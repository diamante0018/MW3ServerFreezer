![license](https://img.shields.io/github/license/diamante0018/MW3ServerFreezer.svg)
[![build](https://github.com/diamante0018/MW3ServerFreezer/workflows/Build/badge.svg)](https://github.com/diamante0018/MW3ServerFreezer/actions)

# MW3ServerFreezer
Remastered MW3 Server Freezer for the 1.4:382 version of the game (client).

## Disclaimer

This software has been created purely for the purposes of academic research. It is not intended to be used to attack other systems. Project maintainers are not responsible or liable for misuse of the software. Use responsibly.

## Summary

This software is a proof of concept for a vulnerability that is patched. You can't harm anyone with it if you use it on Pluto (If you were to update the addresses for the 1.9 patch of the game).
You also can't use this vulnerability on Tekno as it was fixed in 2021 (2.0.6 version of their client).
If you think your server is vulnerable you should seek help in the appropriate discord server or forum of the client you use.
The exploit is documented in [exploit.cpp](src/client/component/exploit.cpp)

## Update

The original patch by the Tekno gods was done incorrectly.

The patch made by Discord user "Zero Bytes" made the Netchan_Process stub return `-1` when suspicious packets were detected.
The return value is completely non-sensical and allows for the execution of SV_PacketEvent to continue.

```c
int __cdecl Netchan_Process_Stub(netchan_t* a1, msg_t* a2)
{
  if ( a2->cursize <= 14 || !a2->data[14] )
    return Netchan_Process_Original(a1, a2);

  // Forces the bytes of the packet to remain within acceptable values
  a2->data[7] = 0;
  a2->data[14] = 0;
  // Returns wrong value. SV_PacketEvent is allowed to continue
  return -1;
}
```

Later revisions of the Tekno gods server DLL seem to have changed this behaviour and now the stub returns `0` when a suspicious packet is detected.
The exploit was finally fixed.

```c
int __cdecl Netchan_Process_Stub(netchan_t* a1, msg_t* a2)
{
  if ( a2->cursize <= 14 || !a2->data[14] )
    return Netchan_Process_Original(a1, a2);

  // Redundant operation
  a2->data[7] = 0;
  a2->data[14] = 0;
  // Returns correct value. SV_PacketEvent will return and it will not process the packet any further
  return 0;
}
```

## Compile from source

- Install [Visual Studio 2022][vs-link] and enable `Desktop development with C++`
- Install [Premake5][premake5-link] and add it to your system PATH
- Clone this repository using [Git][git-link]
- Update the submodules using ``git submodule update --init --recursive``
- Run Premake with the option ``premake5 vs2022`` (Visual Studio 2022). No other build systems are supported.
- Build the project via the solution file in `build\mw3-server-freezer.sln`.

Only the Win32 platform is supported. Do not attempt to build for Windows ARM 64 or x64.

## Commands

List of hard-coded key binds:
- O Activate the exploit
- L Undo the exploit
- K Force disconnect from server (back to main menu)

## Credits

- QUADFOST posted the original exploit on a popular gaming forum. I wrote this software implementing the exploit.

[vs-link]:                https://visualstudio.microsoft.com/vs
[premake5-link]:          https://premake.github.io/download
[git-link]:               https://git-scm.com
