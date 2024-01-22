#!/bin/bash
# bash pathto AgileROHFinder.exe path_To_Folder_Of_VCF_Files either_-t|-b|-a
#i.e. /home/msjimc/AgileROHFinder.exe /data/VCFfiles/ -t

program=$1
folder=$2

echo "Folder of files:"
if [ -d "${folder}" ] ; then
    echo "Good $folder is OK";
elif [ -f "${folder}" ]; then
    echo "Error ${folder} is a file";
    exit 1
else
    echo "Error ${folder} is not valid";
    exit 1
fi

for fileName in $folder/*.vcf
	do
		echo "input file: "$fileName
		outputFile=$(echo $fileName | sed 's/.vcf/.txt/g')
		echo "save data too: "$outputFile
		$program $fileName $outputFile $3
	done

echo "script completed."