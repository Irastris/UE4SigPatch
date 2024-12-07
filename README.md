# UESigPatch
UESigPatch is an ASI plugin with the intent of patching signature checks and subsequently enabling content mods for an increasing number of Unreal Engine 4/5 games. UESigPatch utilizes [MinHook](https://github.com/TsudaKageyu/minhook) and a pattern scanning function written by [@lguilhermee](https://github.com/lguilhermee).

### Disclaimer:
Usage of UESigPatch with games, especially in regard to those which implement any form of online services, is entirely at the risk of the end user. No warranty is provided and UESigPatch's contributors can not be held responsible for damages resulting from its (mis)use, violation of relevant Terms of Service agreements, or any other action. **YOU HAVE BEEN WARNED!**

### Instructions:
Download the compiled ASI from the [latest release](https://github.com/Irastris/UESigPatch/releases/latest), or clone the repository and compile the solution in Visual Studio 2022. To utilize, the ASI should be injected into supported Unreal games using an ASI injector, this repo recommends [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader).

### Supported Games [^1]:
 - Asterigos: Curse of the Stars
 - Black Myth Wukong
 - Bramble: The Mountain King
 - DRAGON BALL Sparking! ZERO
 - Fast Food Simulator Prologue
 - Harry Potter Quidditch Champions
 - inZOI Character Studio Demo
 - Mortal Kombat 1
 - Sifu
 - Slackers - Carts of Glory

### Known Limitations:
At this time, this new UESigPatch V2 has no wildcards for any of its AOBs. This means that any game updates which affect the executable are highly likely to result in UESigPatch needing an update as well. A solution for this is being researched.

[^1]: The supported games list represents compatibility as it stood on December 1st, 2024. Any subsequent games updates may result in this list no longer being accurate.
