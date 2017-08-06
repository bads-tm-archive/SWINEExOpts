# S.W.I.N.E. ExOpts
 Anyone can participate/contribute , you can add your name/info on places where it was strongly modified or added.
 
------------------------------------------------------------------------------------------------------------

# Thanks to:

 In order to save some time, this was used (Thx, Malwin!)
 https://www.youtube.com/watch?v=MzzmW3adSpI
 
 You can get fixed version here: https://github.com/bads-tm/SWINEExOpts/raw/master/S.W.I.N.E.%20Hacker%20v1.1.CT
 
 Somethat was/is based on [NFSCExOpts](https://github.com/nlgzrgn/NFSCExOpts) base

------------------------------------------------------------------------------------------------------------
# How To Compile:

You can compile this with these steps:

1) Open `SWINEExtraOptions\SWINEExtraOptions.vcxproj` with Microsoft Visual Studio 2015 [Any Edition, can be Community or Enterprise]
(If you want to use it with an older version, just change the platform toolset setting.)
2) Look for the "Solution Explorer" panel. Locate "SWINEExtraOptions" under "Solution "SWINEExtraOptions" (1 project)".
3) Right click > Build. (Or, you can open its contents by clicking the triangle at left. dllmain.cpp is the main code. Make the edits you want, you're free!)
!Make sure you're building with Release and Win32 option. See the upper toolbar for them.
4) Look for the "Output" panel. If it says "Build: 1 succeeded, 0 failed," and stuff, your .asi file has been successfully built. (It will be built into `(Project folder)\Release` folder.)
5) Now, copy it to your `*GAME LOCATION*\scripts` folder. (Use Ctrl+C, Ctrl+V / Cmd+C, Cmd+V / Strg+C, Strg+V; Right-Click > Copy; via xcopy command on CMD; or how do you like it.)
6) Copy the SWINEExtraOptionsSettings.ini from main folder into `*GAME LOCATION*\scripts` folder, too.
7) Run Game and see what happens. :)
If not get this https://github.com/ThirteenAG/Ultimate-ASI-Loader/ and put into "GAME LOCATION" folder (main one near game launcher / exectutable) rename dll file to d3d8 And try again.

Alternative Compiling: Build.bat [Still M$ Visual Studio]
1) Start build.bat and hopefully it compiles!

Alternative compling : GNU GCC [Compile for Windows from Linux?]

1) Use GNU GCC https://gcc.gnu.org/
2) should be something like
` g++ <your-source.cpp> -o <output name> `

Some internetz help to you https://stackoverflow.com/questions/2033997/how-to-compile-for-windows-on-linux-with-gcc-g
http://www.blogcompiler.com/2010/07/11/compile-for-windows-on-linux/
https://stackoverflow.com/questions/38786014/how-to-compile-executable-for-windows-with-gcc-with-linux-subsystem

------------------------------------------------------------------------------------------------------------
### This ExOpts Team/Members:
1. @steakhal https://github.com/steakhal
2. @bads-tm https://github.com/bads-tm/
3. @nlgzrgn (because NFSCExOpts was used as base) https://github.com/nlgzrgn/
------------------------------------------------------------------------------------------------------------
# © 2017 ExOpts Team/Members