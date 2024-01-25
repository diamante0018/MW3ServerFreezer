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
The exploit is documented in [exploit.cpp](https://github.com/diamante0018/MW3ServerFreezer/blob/main/src/client/component/exploit.cpp)

## Update

The original patch by the Tekno gods was done incorrectly.

The patch made by Discord user "Zero Bytes" made the Netchan_Process stub return `-1` when suspicious packets were detected.
The return value is completely non-sensical and allows for the execution of SV_PacketEvent to continue.

```c
int __cdecl Netchan_Process_stub(netchan_t* a1, msg_t* a2)
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

```c
int __cdecl Netchan_Process_stub(netchan_t* a1, msg_t* a2)
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

- Clone the Git repo. Do NOT download it as ZIP, that won't work.
- Update the submodules and run `premake5 vs2022` or simply use the delivered `generate.bat`.
- Build via solution file in `build\mw3-server-freezer.sln`.

## Commands

List of hard-coded key binds:
- O Activate the exploit
- L Undo the exploit
- K Force disconnect from server (back to main menu)

## Credits

- QUADFOST posted the original exploit on a popular gaming forum. I wrote this software implementing the exploit.
