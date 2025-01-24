#!/bin/bash

# Variables
APP_NAME="codeeditor"
VERSION="1.0"
MAINTAINER="Fajar Julyana <fajarjulyana1@gmail.com>"
DESCRIPTION="A simple code editor with syntax highlighting and dark mode."
BUILD_DIR="build"
DEB_DIR="$BUILD_DIR/$APP_NAME-$VERSION"
BIN_DIR="$DEB_DIR/usr/bin"
DESKTOP_DIR="$DEB_DIR/usr/share/applications"
ICON_DIR="$DEB_DIR/usr/share/icons/hicolor/128x128/apps"

# Step 1: Clean previous build
rm -rf $BUILD_DIR
mkdir -p $BIN_DIR $DESKTOP_DIR $ICON_DIR $DEB_DIR/DEBIAN

# Step 2: Compile the application
echo "Compiling the application..."
moc -o moc_CodeEditor.cpp CodeEditor.h
g++ -fPIC main.cpp CodeEditor.cpp moc_CodeEditor.cpp -o codeeditor `pkg-config --cflags --libs Qt5Widgets`

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Step 3: Copy files
echo "Setting up package structure..."
cp codeeditor $BIN_DIR/
cp assets/codeeditor.png $ICON_DIR/

# Step 4: Create .desktop file
cat <<EOF > $DESKTOP_DIR/codeeditor.desktop
[Desktop Entry]
Version=$VERSION
Name=CodeEditor
Comment=$DESCRIPTION
Exec=/usr/bin/codeeditor
Icon=codeeditor
Terminal=false
Type=Application
Categories=Development;Utility;TextEditor;
EOF

# Step 5: Create control file
cat <<EOF > $DEB_DIR/DEBIAN/control
Package: $APP_NAME
Version: $VERSION
Section: utils
Priority: optional
Architecture: amd64
Maintainer: $MAINTAINER
Description: $DESCRIPTION
EOF

# Step 6: Build the .deb package
echo "Building the .deb package..."
dpkg-deb --build $DEB_DIR

if [ $? -eq 0 ]; then
    echo "Package built successfully!"
    mv $BUILD_DIR/$APP_NAME-$VERSION.deb $BUILD_DIR/${APP_NAME}_${VERSION}_amd64.deb
    echo "Your .deb package is ready: $BUILD_DIR/${APP_NAME}_${VERSION}_amd64.deb"
else
    echo "Failed to build the package!"
    exit 1
fi
