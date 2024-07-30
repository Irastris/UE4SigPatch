# UESigPatch
UESigPatch is an ASI plugin with the intent of patching signature checks and subsequently enabling content mods for an increasing number of Unreal Engine 4/5 games, based on the incredible work of [@thethiny](https://github.com/thethiny) and [@ermaccer](https://github.com/ermaccer).

### Disclaimer:
Usage of UESigPatch with games, especially in regard to those which implement any form of online services, is entirely at the risk of the end user. No warranty is provided and UESigPatch's contributors can not be held responsible for damages resulting from its (mis)use, violation of relevant Terms of Service agreements, or any other action. **YOU HAVE BEEN WARNED!**

### Instructions:
Download the compiled ASI from the [latest release](https://github.com/Irastris/UESigPatch/releases/latest), or clone the repository and compile the solution in Visual Studio 2022. To utilize, the ASI should be injected into supported Unreal games using an ASI injector, this repo recommends [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader).

### Supported Games:
 - Asterigos: Curse of the Stars
 - Bramble: The Mountain King
 - Mortal Kombat 1 (by [@thethiny](https://github.com/thethiny))
 - Sifu
 - SOUTH PARK: SNOW DAY!
 - Suicide Squad: Kill The Justice League [^1] [^2]

### Partially Supported Games:
 - The First Descendant [^2] (while patch allows unsigned content, it currently breaks all localized strings)

### Previously Supported Games:
 - Killer Klowns from Outer Space [^3]

[^1]: Games which direct to this footnote require adding `-fileopenlog` to your launch parameters.
[^2]: Games which direct to this footnote require disabling or bypassing anti-cheat services, support for doing so will not be provided by this repository or its contributors.
[^3]: Games which direct to this footnote were once supported, but due to EAC now being verified server-side are no longer functional. The code remains in UESigPatch for the sake of posterity.
