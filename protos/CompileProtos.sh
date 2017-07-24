#!/bin/bash

protoc -I=./src --cpp_out=./protos ./src/*.proto