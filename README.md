# MusicSheetCompiler

Tools used in the package:
1. convert command: ImageMagick 6.9.7-4
Used to convert pdf files to pgm
Issues may have: convert: not authorized `a.pdf' @ error/constitute.c/WriteImage/1028.
edited file /etc/ImageMagick-6/policy.xml
change 
policy domain="coder" rights="none" pattern="PDF"
to
policy domain="coder" rights="read|write" pattern="PDF"
