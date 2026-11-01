# -------------------------
# Class 10: Check if Camera is Accessible
# -------------------------

# Step 1: Import Libraries
import cv2

# Step 2: Setup Camera
cap = cv2.VideoCapture(0)
print("Camera opened:", cap.isOpened())

# Step 3: Read First Frame
success, img = cap.read()
print("First frame success:", success)
