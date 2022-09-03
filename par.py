#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import zipfile
import os
from os.path import basename

source=sys.argv[1]
archive=sys.argv[2]

if(source=="-x"):
    with zipfile.ZipFile(archive,'r') as arch:
        arch.extractall('file_extract')

else:
    with zipfile.ZipFile(archive,'w') as arch:
        for folderName,subfolders,filenames in os.walk(source):
            for filename in filenames:
                filePath=os.path.join(folderName,filename)
                arch.write(filePath,basename(filePath))




