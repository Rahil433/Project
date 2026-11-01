# -------------------------
# Class 12: Hand Detection and Finger Counting
# -------------------------

# Step 1: Import Libraries
import cv2
from cvzone.HandTrackingModule import HandDetector

# Step 2: Setup Camera and Hand Detector
cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands=1, detectionCon=0.8)

# Step 3: Main Loop
while True:
    success, img = cap.read()
    if not success:
        print("Camera not accessible")
        break

    # Step 3a: Detect hands
    hands, img = detector.findHands(img)

    # Step 3b: Finger counting
    if hands:
        hand1 = hands[0]
        fingers = detector.fingersUp(hand1)  # List like [0,1,1,0,0]

    # Step 3c: Show live video
    cv2.imshow("Live Camera Feed", img)

    # Step 3d: Exit on 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Step 4: Release Resources
cap.release()
cv2.destroyAllWindows()