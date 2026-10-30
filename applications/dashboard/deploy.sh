#!/bin/bash
set -e

PI_IP="100.71.83.72"
TARGET_NAME="cybit"
REMOTE_PATH="/usr/bin/$TARGET_NAME"
BUILD_DIR="build-rpi"

echo "==> Cleaning previous build artifacts in $BUILD_DIR..."
cmake --build "$BUILD_DIR" --target clean

echo "==> Building fresh ARM64 binary with updated assets..."
cmake --build "$BUILD_DIR" -j$(nproc)

echo "==> Verifying binary architecture:"
file "$BUILD_DIR/$TARGET_NAME"

echo "==> Deploying binary to Pi ($PI_IP)..."
ssh root@$PI_IP "killall -9 $TARGET_NAME 2>/dev/null || true"
ssh root@$PI_IP "cat > $REMOTE_PATH" < "$BUILD_DIR/$TARGET_NAME"
ssh root@$PI_IP "chmod +x $REMOTE_PATH"
# Keep /opt in sync
ssh root@$PI_IP "mkdir -p /opt/cyberdeck && cp $REMOTE_PATH /opt/cyberdeck/$TARGET_NAME"

echo "==> Restarting dashboard on framebuffer..."
ssh root@$PI_IP "
    QT_QPA_PLATFORM='linuxfb:fb=/dev/fb0:size=720x480' $REMOTE_PATH > /tmp/$TARGET_NAME.log 2>&1 &
"

echo "==> Deployed successfully. Monitoring log:"
sleep 2
ssh root@$PI_IP "cat /tmp/$TARGET_NAME.log"
