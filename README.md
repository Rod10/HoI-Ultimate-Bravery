
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

![Main Menu](https://cdn.discordapp.com/attachments/1212383699191070801/1281173605517885463/image.png?ex=66dac166&is=66d96fe6&hm=9a0d0bd1c4bc712195acf1c25a912c46ec0e1f99212f4f46c45eb1671e59248f&)

HoI Ultimate Bravery is an external program allowing you to randomly generate unit types such as tanks/planes/boats as well as the divisions themselves. For now it only work with the base game (will all the DLC, maybe ?) and in the futur i will include the support of generating unit for mod.
You can choose the nations which will have the right to have these units but there is a small catch: you cannot, inside the game, change/edit the units or divisions you have generated.

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
![Generate Menu](https://cdn.discordapp.com/attachments/1212383699191070801/1212383709949337650/image.png?ex=66d9ab51&is=66d859d1&hm=83f43d4f345a73fcbf175f4708a8bd823332c7a9ac93e4f7e6a320ee3be3f189&)You can choose the nation you want to play and generate the units you want or do it for all the nations present in the selection by checking the box

When you click on the type you want to generate you get this
![Generation Window](https://cdn.discordapp.com/attachments/1212383699191070801/1212385828504997888/image.png?ex=66d9ad4a&is=66d85bca&hm=15b023aa03eee74c2c5c8ce2d7107faf885a336b708dddb40011d286acde2379&)
You can go back or regenerate

When you are on import page you can select wich countries you want to import or just click the checkbox for all countries.
![Import Menu](https://cdn.discordapp.com/attachments/1212383699191070801/1212401969868574810/image.png?ex=66d91392&is=66d7c212&hm=dd0e1b6bc3cca909f1a9fc0a1591cc2ac9fab5f3afb6212b010c529e35acd990&)
You'll need to import before starting the game and be ultra careful to reset file before quitting the program else you are good to do a steam verif of your game.

<!--_For more examples, please refer to the [Documentation](https://example.com)_-->

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] look on how i can make this thing responsive 😑 (WIP)
- [ ] Find good color that make the thing better
- [ ] Learn math to show the right base stats*
- [ ] Look if we can reset file while exiting the program
- [ ] Choose the type of division to generate (infantry/motorised/full random)
- [ ] The possibility of not having all the DLC
- [ ] Add multiplayer support 
- [ ] Mod integration (Not in order for overhaul mod)
	- [ ] Infantry Equipment
	- [ ] Expanded Designers Combined
	- [ ] Extended Support Company (10 slots)
	- [ ] RoadTo56
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
		- [ ] Divisions
		- [ ] Doctrines
			- [ ] Infantry
			- [ ] Ship
			- [ ] Plane
			- [ ] Special
	- [ ] Millenium Dawn
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
		- [ ] Divisions
		- [ ] Doctrines
			- [ ] Infantry
			- [ ] Ship
			- [ ] Plane
			- [ ] Special
	- [ ] KaiserReich
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
		- [ ] Divisions
		- [ ] Doctrines
			- [ ] Infantry
			- [ ] Ship
			- [ ] Plane
			- [ ] Special
	- [ ] KaiserReichRedux
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
		- [ ] Divisions
		- [ ] Doctrines
			- [ ] Infantry
			- [ ] Ship
			- [ ] Plane
			- [ ] Special
	- [ ] Darkest Hour
		- [ ] Divisions
		- [ ] Doctrines
			- [ ] Infantry
			- [ ] Ship
			- [ ] Plane
	- [ ] World Ablaze (☠️)
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
		- [ ] Divisions
		- [ ] Doctrines
			- [ ] Infantry
			- [ ] Ship
			- [ ] Plane
			- [ ] Special
	- [ ] Black Ice (☠️)
		- [ ] Tanks
		- [ ] Planes
		- [ ] Ships
		- [ ] Divisions
		- [ ] Doctrines
			- [ ] Infantry
			- [ ] Ship
			- [ ] Plane
			- [ ] Special
	- [ ] Equestria at War (Yes i know but why not ?)

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
