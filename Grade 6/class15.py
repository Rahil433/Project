# -------------------------
# Hand Gesture to ESP32 Python Program
# Phase I: Detection + Gesture Display + Serial Communication
# -------------------------

# Step 1: Import Libraries
import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import time

# -------------------------
# Step 2: Setup ESP32 Serial Connection
# -------------------------
esp = serial.Serial('COM3', 9600)  # Replace COM3 with your ESP32 port
time.sleep(2)  # Wait for ESP32 to initialize

last_sent_command = ""  # Stores last sent command to avoid duplicates

def send_command(command):
    """Send gesture command to ESP32 only if it's new"""
    global last_sent_command
    if command != last_sent_command:
        esp.write(command.encode())  # Convert string to bytes for serial
        print(f"Sent to ESP32: {command}")
        last_sent_command = command

# -------------------------
# Step 3: Setup Camera and Hand Detector
# -------------------------
cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands=1, detectionCon=0.8)

# -------------------------
# Step 4: Gesture Debounce Logic Variables
# -------------------------
STABLE_FRAMES_REQUIRED = 10
gesture_counter = 0
current_gesture = ""

# -------------------------
# Step 5: Helper Function to Display Gesture on Screen
# -------------------------
def draw_gesture_label(image, gesture):
    """Display detected gesture text on video frame"""
    cv2.putText(image, gesture, (20, 50),
                cv2.FONT_HERSHEY_SIMPLEX, 2,
                (0, 255, 0), 3)

# -------------------------
# Step 6: Main Loop
# -------------------------
while True:
    success, img = cap.read()
    if not success:
        print("Camera not accessible")
        break

    # Step 6a: Detect hands
    hands, img = detector.findHands(img)

    # Step 6b: Finger counting and gesture mapping
    if hands:
        hand1 = hands[0]
        fingers = detector.fingersUp(hand1)  # List like [0,1,1,0,0]

        # Map finger patterns to gestures
        if fingers == [0, 1, 0, 0, 0]:
            gesture = "ONE"
        elif fingers == [0, 1, 1, 0, 0]:
            gesture = "TWO"
        elif fingers == [0, 1, 1, 1, 0]:
            gesture = "THREE"
        elif fingers == [0, 1, 1, 1, 1]:
            gesture = "FOUR"
        elif fingers == [1, 1, 1, 1, 1]:
            gesture = "FIVE"
        else:
            gesture = "UNKNOWN"

        # Step 6c: Debounce Logic
        if gesture == current_gesture:
            gesture_counter += 1
        else:
            current_gesture = gesture
            gesture_counter = 1

        # Step 6d: Send command if stable
        if gesture_counter >= STABLE_FRAMES_REQUIRED and gesture != "UNKNOWN":
            send_command(gesture)

        # Step 6e: Display gesture
        draw_gesture_label(img, gesture)
    else:
        # No hand detected → reset
        current_gesture = ""
        gesture_counter = 0

    # Step 6f: Show live video
    cv2.imshow("Live Camera Feed", img)

    # Step 6g: Exit on 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# -------------------------
# Step 7: Release Resources
# -------------------------
cap.release() 
cv2.destroyAllWindows()
esp.close()
print("Program ended, serial port closed.")