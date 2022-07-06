#!/usr/bin/env sh

TARGET_DIR=$HOME/lib
VERSION=$(git log --date=format-local:'%Y %b %d|%H:%M' --format='[%Cgreen%ad%Creset] %C(auto)%h' | head -n 1)
echo "/* Release: $VERSION */" > temp
cat temp src/utillyty.h > $TARGET_DIR/utillyty.h
rm temp
echo "Released version: $VERSION, directory: $TARGET_DIR"