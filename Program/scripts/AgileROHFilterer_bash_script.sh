#!/bin/bash
# bash pathto AgileROHFilterer.exe path_To_Folder_Of_VCF_Files either_-t|-b|-a
#i.e. /home/msjimc/AgileROHFilterer.exe /data/VCFfiles/ 500000 -t

program=$1
folder=$2
extend=$3
options=$4


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
		outputVCFFile=$(echo $fileName | sed 's/.vcf/._filtered.vcf/g')
		echo "save data too: "$outputFile
		$program $fileName $outputVCFFile $outputFile $extend $options
	done

echo "script completed."