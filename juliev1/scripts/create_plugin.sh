#!/bin/bash

echo "Enter the plugin name (lowercase)"
read plugin_name_lower
echo "Enter the plugin name (normal)"
read plugin_name_normal
echo "Enter the plugin name (capital)"
read plugin_name_capital

mkdir ../plugins/$plugin_name_lower
cp -R ../plugins/echo/* ../plugins/$plugin_name_lower 
cd ../plugins/$plugin_name_lower/
cat CMakeLists.txt | sed "s/echo/$plugin_name_lower/g" | sed "s/Echo/$plugin_name_normal/g" | sed "s/ECHO/$plugin_name_capital/g" > CMakeLists.txt
cat echo.h | sed "s/echo/$plugin_name_lower/g" | sed "s/Echo/$plugin_name_normal/g" | sed "s/ECHO/$plugin_name_capital/g" > $plugin_name_lower.h
cat echo.cpp | sed "s/echo/$plugin_name_lower/g" | sed "s/Echo/$plugin_name_normal/g" | sed "s/ECHO/$plugin_name_capital/g" > $plugin_name_lower.cpp

rm echo.h
rm echo.cpp

