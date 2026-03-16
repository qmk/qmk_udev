#!/bin/sh
# Vendors tools/include/nolibc from a pinned Linux kernel tag.
# Usage: ./update-nolibc.sh [tag]   (default: v6.13)

set -e

TAG="${1:-v6.19}"
DEST="nolibc"
KERNEL_REPO="https://github.com/torvalds/linux.git"
SPARSE_PATH="tools/include/nolibc"

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

echo "Fetching nolibc @ $TAG ..."
git clone --depth=1 --no-checkout --filter=blob:none \
    --branch "$TAG" "$KERNEL_REPO" "$TMP"
git -C "$TMP" sparse-checkout set "$SPARSE_PATH"
git -C "$TMP" checkout

rm -rf "$DEST"
cp -r "$TMP/$SPARSE_PATH" "$DEST"

echo "Done. nolibc vendored from Linux $TAG into $DEST/"
