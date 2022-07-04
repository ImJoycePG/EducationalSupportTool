<h1 align="center"> EducationalSupportTool </h1>

We are a group from the Universidad Privada del Norte that is developing a tool to help initial students. It is not the best but we are improving it little by little

<h1 align="left"> Libraries </h1>

<br>

- **FREEGLUT:** https://www.transmissionzero.co.uk/software/freeglut-devel/
- **GLEW:** http://glew.sourceforge.net/
- **GLM:** https://github.com/g-truc/glm
- **GLUI:** https://github.com/libglui/glui | **x64:** https://drive.google.com/drive/folders/1cqV36neOBPcEdXPbmIJlBh-XWOLI_YcZ?usp=sharing

<h1 align="left"> How to import libraries </h1>

To import the libraries follow these steps:

1. Once you clone the project or create a new project you must go to the configuration or properties of the project (EducationalSupportTool Properties)

![image](https://user-images.githubusercontent.com/104446699/174503972-726ec4fc-e844-4e77-9031-6cdb5a6cb7d8.png)

2. Now go to the "C/C++" section and into the additional include directories

![image](https://user-images.githubusercontent.com/104446699/174504024-b6f53caa-700e-4c19-8736-21ebfe533b11.png)

3. You have to edit all this and include the "include" folder of each library

![image](https://user-images.githubusercontent.com/104446699/174504038-e6059366-f0ed-4341-a67f-323484ca4e20.png)

4. Now you need to go to the Linker section and find the additional library directories

![image](https://user-images.githubusercontent.com/104446699/174504070-5ef0f945-b506-4af0-82e6-30c945f7894b.png)

5. You must add the "Libs" folders of each library that we are going to import. I should mention that my compiler is 64 bit

![image](https://user-images.githubusercontent.com/104446699/174504097-c7206225-b18e-4173-801e-23ad92ae8aa7.png)

6. Now within the same section you will need to search for "Input" and edit the additional dependencies

![image](https://user-images.githubusercontent.com/104446699/174504107-d0c90706-1826-4888-ac75-2d5be62f01bb.png)

7. You must add those two libraries (freeglut.lib and glew32.lib)

![image](https://user-images.githubusercontent.com/104446699/174504144-48339ac0-b648-4f20-a0d4-b277d06169f3.png)


<h1 align="center"> Bugs? </h1>

![image](https://user-images.githubusercontent.com/104446699/174504233-dd64d4a8-39b4-426b-8788-2d2d623e9cde.png)

**Solution:**

Add _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING, _ITERATOR_DEBUG_LEVEL=0 to Preprocessor definitions.

Project -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions.

![image](https://user-images.githubusercontent.com/104446699/177203484-89ac1852-e97d-469c-958b-26603cc17a7e.png)

**Solution:**

![image](https://user-images.githubusercontent.com/104446699/177203503-74685ed5-5373-4e88-a9ad-3ee6a89df22a.png)

Change Debug to Release.


This solved the issue for me.

<h2 align="center">My stats</h3>

<p align="left">
    <a href="https://discord.com/users/299732456037154817" target="_blank" rel="nofollow">
        <img src="https://lanyard-profile-readme.vercel.app/api/299732456037154817?&animated=true&borderRadius=30px&idleMessage=Nothing..." alt="Discord Presence" align="center">
    </a>
</p>

<!-- <div> -->
<p align="left">
<a>
<img align="center" src="https://github-readme-stats.vercel.app/api?username=imjoycepg&show_icons=true&theme=radical&count_private=true&locale=en" alt="imjoycepg" />
</a>
</p>

<p align="left">
<img src="https://github-readme-stats.vercel.app/api/top-langs?username=imjoycepg&show_icons=true&theme=radical&locale=en&layout=compact" alt="imjoycepg" />
</p>
