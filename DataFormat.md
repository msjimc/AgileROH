## Data file format

### VCF text files with .vcf extension 
VCF files have a complex structure with the start consisting of a number of lines starting with '##' that describe the data format in the rest of the file. This is followed by a single line starting with '#' that describes the fields/columns in the remained of the file as described in the table below. The contents of the __FORMAT__ and __Sample__ columns are variable with the requirements of AgileROH outlined in the 2nd table.


|Header|Description|Possible values|Note|Required|
|-|-|-|-|-|
|#CHROM|Chromosome|The name of the reference sequence in the genome. For autosomal chromosomes it is a number (1-22). X, Y and MT typically refere to the sex chromosomes and mitrochondria. Other sequences may be present that contain unlocated sequences, common viruses or common alternative haplotypes these tend to have complex names. These names may have the 'chr' prefix.|Only values of 1 to 22 or chr1 to chr22 are retained|Yes|
|POS|Position|Variants location in the reference sequence (The first base of the reference may be referenced as 0 and not 1).|Any whole number|Yes|
|ID|Variant name| This can be any text value, but is typically either a RS id or a '.'|AgileROH may filter variants based on the presence of 'RS' at the start of the name|Optional|
|REF|Variant's wild type allele|Any possible sequence of A, C, G and T|Only alleles of one nucleotide are retained|Yes|
|ALT|Variant's alternative allele(s)|Any possible sequence of A, C, G and T. If a variant is heterozygous for two none reference alleles each allele will be separated by a ','.|Only variants with a single 1 base alelle are retained and |Yes|
|QUAL|Quality score|Any number or '.'|An aligner and variant caller specific score of the variant's quality|No|
|FILTER|Variant filtering describing any filtering performed on the data|Any value|Not used|No|
|INFO|Variant specific data created by variant caller|List of key value pairs||No|
|FORMAT|Structure and format of variant specific data, written as a series of keys (described in the header section) separated by ':'.|Contents or variable depending on variant caller and variant type|See below|Yes| 
|\<JT706\> (Sample/patient name)|Text and or numbers|Variant specific data as described in the __FORMAT__ column|Contents or variable depending on variant caller and variant type|Yes|

The contents of the __Format__ and __Sample__ columns are variable, being variant caller and variant type specific. For example a VCF file created by GATK's 'haplotypecaller' may have a format field like this ' GT:AD:DP:GQ:PL', table below discribes its structure.

|Key|Value|Description|Required|
|-|-|-|-|
|GT|Variant's genotype|Each alelle is number with the reference allele = 0 and the alternaive allele given by its positon in the Alt column list of alleles. AgileROH ignores variants with multiple alternative alleles so this value is always 1. Homozygous variants are shown as 1/1, while heterozygous positions or 0/1 (homozygous refernce genotypes are typically not present)|No| 
|AD|Two numbers separeted by a ','|Allelic depths for the ref and alt alleles in the order listed|Yes|
|DP|Number|Approximate read depth (poor quality reads may be ignored)|No|
|GQ|Number|Genotype Quality as calculated by the variant caller|No|
|PL|Three numbers seperated by ','|Normalized, Phred-scaled likelihoods for genotypes as defined in the VCF specification|No|

AS can be seen from the two tables AgileROH requires the chromosome, position and allele data that is always present in a vcf file. However, it also requires the allele read depth and total read depth data points in columns 9 and 10 of a file, which may be omitted by some variant callers. Consequently it is suggested that GATK's haplotypecaller is used to make the files.

### Affymetrix tab-delimited text files with .xls extension 

|Header|Chromosome|Chromosomal Position|dbSNP RS ID|Call|
|-|-|-|-|-|
|Data type|Text with or without 'chr' prefix|Number|Text|Text (AA, AB, BB or NoCall)|


### Affymetrix birdseed files files with .xtxtls extension 

|Header|Chromosome|Chromosomal Position|dbSNP RS ID|Call|
|-|-|-|-|-|
|Data type|Text with or without 'chr' prefix|Number|Text|Text (AA, AB, BB or NoCall)|
