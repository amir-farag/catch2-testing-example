cmake_minimum_required(VERSION 3.8)
project(Code CXX)
set(SOURCE_FILES
        Receiver.cpp
        Receiver.h
        Sender.cpp
        Sender.h)
add_library(Code ${SOURCE_FILES} )