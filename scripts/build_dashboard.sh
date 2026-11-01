#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
REPO_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/../.." && pwd)
DASHBOARD_DIR="$REPO_ROOT/cybit_rpi/applications/dashboard"
BUILD_DIR="${DASHBOARD_BUILD_DIR:-$DASHBOARD_DIR/build-rpi}"
OVERLAY_DIR="${ROOTFS_OVERLAY_DIR:-$REPO_ROOT/cybit_rpi/board/raspberrypizero2w-64/rootfs-overlay}"
OUTPUT="$OVERLAY_DIR/usr/bin/cybit"

if [ ! -f "$BUILD_DIR/Makefile" ]; then
    echo "Dashboard build is not configured: $BUILD_DIR" >&2
    echo "Configure it with the Raspberry Pi cross toolchain before building the image." >&2
    exit 1
fi

cmake --build "$BUILD_DIR" --target clean
cmake --build "$BUILD_DIR" --parallel "${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)}"

if [ ! -x "$BUILD_DIR/cybit" ]; then
    echo "Dashboard build did not produce an executable: $BUILD_DIR/cybit" >&2
    exit 1
fi

mkdir -p "$(dirname -- "$OUTPUT")"
TMP_OUTPUT="$OUTPUT.tmp.$$"
trap 'rm -f "$TMP_OUTPUT"' EXIT HUP INT TERM
install -m 0755 "$BUILD_DIR/cybit" "$TMP_OUTPUT"
mv -f "$TMP_OUTPUT" "$OUTPUT"
trap - EXIT HUP INT TERM
printf 'Staged dashboard at %s\n' "$OUTPUT"
