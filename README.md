# XlogDecode
Source code of win32 tool which is used to decode the xlog written by tencent.

Project was compiled on visual studio 2008 on windows 7 64.

Anyone who wants to compiled on vs2015(or vs2017) just need to copy the source to your new project 

and set *.c files in zlib to not using pre-compile header.

remember to add all files to your project, enjoy it :)

contact:124928918@qq.com

中文：

win32下解码xlog的工具。

xlog为腾讯开源mars工程里的log模块，对保存的xlog文件进行了压缩和加密，并且目前只提供了python工具用于解密xlog文件。

当需要在任意PC电脑查看加密的LOG内容时，需要安装python才能进行解密，极其不方便。

因此编写了上述工具，可直接拖放xlog文件点击解密即可在.xlog文件路径下生成.log的同名解密文件。

源码说明：

zlib移植自mars, 编译工程需要将zlib下的.C文件选择not using pre-compile header。其他代码自己编写。

联系方式：124928918@qq.com
