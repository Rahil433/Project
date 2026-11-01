# -------------------------
# Class 11: Capturing Frames and Showing Live Video
# -------------------------

# Step 1: Import Libraries
import cv2

# Step 2: Setup Camera
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Camera not accessible")
    exit()

# Step 3: Main Loop
while True:
    success, img = cap.read()
    if not success:
        print("Camera not accessible")
        break

    # Show live video
    cv2.imshow("Live Camera Feed", img)

    # Exit on 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Step 4: Release Resources
cap.release()
cv2.destroyAllWindows()