# -------------------------
# Class 13: Gesture Mapping and Debounce Logic
# -------------------------

# Step 1: Import Libraries
import cv2
from cvzone.HandTrackingModule import HandDetector

# Step 2: Setup Camera and Hand Detector
cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands=1, detectionCon=0.8)

# Step 3: Gesture Debounce Logic Variables
STABLE_FRAMES_REQUIRED = 10
gesture_counter = 0
current_gesture = ""

# Step 4: Main Loop
while True:
    success, img = cap.read()
    if not success:
        print("Camera not accessible")
        break

    # Step 4a: Detect hands
    hands, img = detector.findHands(img)

    # Step 4b: Finger counting and gesture mapping
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

        # Step 4c: Debounce Logic
        if gesture == current_gesture:
            gesture_counter += 1
        else:
            current_gesture = gesture
            gesture_counter = 1
    else:
        # No hand detected -> reset
        current_gesture = ""
        gesture_counter = 0

    # Step 4d: Show live video
    cv2.imshow("Live Camera Feed", img)

    # Step 4e: Exit on 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Step 5: Release Resources
cap.release()
cv2.destroyAllWindows()