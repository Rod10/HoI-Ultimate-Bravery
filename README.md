
<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-raw/Rod10/HoI-Ultimate-Bravery?style=for-the-badge)
![GitHub Release](https://img.shields.io/github/v/release/Rod10/HoI-Ultimate-Bravery?style=for-the-badge)



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Rod10/HoI-Ultimate-Bravery">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Hoi Ultimate Bravery</h3>

  <p align="center">
    An external program for Heart Of Iron IV
    <br />
    <a href="https://github.com/Rod10/HoI-Ultimate-Bravery"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Rod10/HoI-Ultimate-Bravery">View Demo</a>
    ·
    <a href="https://github.com/Rod10/HoI-Ultimate-Bravery/issues">Report Bug</a>
    ·
    <a href="https://github.com/Rod10/HoI-Ultimate-Bravery/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

![Main Menu](https://cdn.discordapp.com/attachments/388277885099704321/1212336755051864064/image.png?ex=65f17796&is=65df0296&hm=19876ea60b637541917c85060f72bc299edecb1ea1b42ac0eb00a7ab161db029&)

HoI Ultimate Bravery is an external program allowing you to randomly generate unit types such as tanks/planes/boats as well as the divisions themselves. 
You can choose the nations which will have the right to have these units but there is a small catch: you cannot, inside the game, change/edit the units already present.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

![Static Badge](https://img.shields.io/badge/C%2B%2B-%2300599C?style=for-the-badge&logo=C%2B%2B)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

```sh
  Heart Of Iron IV
  All the DLC (for now)
  A C++ IDE if you want to participate in the project
  ```

### Installation

1. Clone the repo (don't clone it in folder C:/xxx/xxx)
   ```sh
   (with ssh) git clone git@github.com:Rod10/HoI-Ultimate-Bravery.git
   (w/o ssh)  git clone https://github.com/Rod10/HoI-Ultimate-Bravery.git
   ```
2. Launching, with administator, the app with the .exe or with compilation in your IDE 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

The UI is divided in two part:
On the left you have the buttons to navigate through the different menus
On the right you have a box where the different elements are located to generate your units

The first thing you'll need to do is to set the game path in the options
(don't mind the language options, it can broke the whole thing)

You can now go to Generate, you can choose the unit type on the left and the unit subtype
![Generate Menu](https://cdn.discordapp.com/attachments/1212383699191070801/1212383709949337650/image.png?ex=65f1a351&is=65df2e51&hm=44e1a92d8abb06023981a8c12b01d831972a195573761bca7a38c8af2f666af2&)You can choose the nation you want to play and generate the units you want or do it for all the nations present in the selection by checking the box

When you click on the type you want to generate you get this
![Generation Window](https://cdn.discordapp.com/attachments/1212383699191070801/1212385916405026816/image.png?ex=65f1a55f&is=65df305f&hm=b0541a15a101d0f66dc6c02b869436cf4fdae04733740798569b5d316224bf6e&)
You can go back or regenerate

When you are on import page you can select wich countries you want to import or just click the checkbox for all countries.
![Import Menu](https://cdn.discordapp.com/attachments/1212383699191070801/1212401969868574810/image.png?ex=65f1b452&is=65df3f52&hm=db81a0f9ca403ba2884cff33eb50d026637955120a99c232712bccf9cbd3a9ab&)
You'll need to import before starting the game and be ultra careful reset file before quitting the program else you are good to do a steam verif of your game.

<!--_For more examples, please refer to the [Documentation](https://example.com)_-->

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Learn math do show the right base stats*
- [ ] Choose the type of division to generate (infantry/motorised/full random)
- [ ] The possibility of not having all the DLC
- [ ] Add multiplayer support 
- [ ] Mod integration
	- [ ] Infantry Equipment
	- [ ] Expanded Designers Combined
	- [ ] RoadTo56
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
	- [ ] Millenium Dawn
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
	- [ ] KaiserReich
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
	- [ ] KaiserReichRedux
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships

*Without doctrine/research/...

See the [open issues](https://github.com/Rod10/HoI-Ultimate-Bravery/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Erwan Billy - [@Rod24](https://twitter.com/Rod2448) - erwan.billy@hotmail.fr

Project Link: [https://github.com/Rod10/HoI-Ultimate-Bravery](https://github.com/Rod10/HoI-Ultimate-Bravery)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/Rod10/HoI-Ultimate-Bravery/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
