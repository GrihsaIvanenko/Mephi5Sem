#!/bin/bash

comm=$(ps -eo fuser,user,comm)
echo $comm
