cscript configure.js threads=yes^ http=no^ html=no^ c14n=no^ catalog=no^ xpath=no^ xptr=no^ xinclude=no^ iconv=no^ icu=no^ iso8859x=no^ zlib=no^ lzma=no^ xml_debug=yes^ regexps=no^ modules=no^ tree=yes^ reader=yes^ writer=yes^ walker=no^ pattern=no^ push=yes^ valid=no^ sax1=no^ legacy=no^ output=yes^ schemas=no^ schematron=no^ python=no^ compiler=msvc^ cruntime=/MTd^ dynruntime=yes^ vcmanifest=no^ debug=yes^ static=yes^ include=..\\include\\libxml^ 

nmake /f Makefile.msvc libxmla

move /y .\\bin.msvc\\Libxml2_a.lib ..\\bin\\LibXML.lib

