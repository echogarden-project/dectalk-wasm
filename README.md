# DECtalk speech synthesizer (WebAssembly port)

[DECtalk](https://en.wikipedia.org/wiki/DECtalk) was a speech synthesizer developed by Digital Equipment Corporation in 1983. It was also known as the voice of Stephen Hawking.

This is a WebAssembly port of [C source code](https://github.com/dectalk/dectalk) that was published in 2015 and 2022 by the original developers.

## Installation

```
npm install @echogarden/dectalk-wasm
```

## Usage

```ts
import { synthesize, DecTalkVoice } from './DecTalk.js'

const simpleText = 'Hello World! How are you doing today?'

const outputFileContent = await synthesize(simpleText, {
	voice: DecTalkVoice.Paul,
	rate: 150,
})

const { writeFile } = await import('fs/promises')
await writeFile('out/out.wav', outputFileContent)
```

## Available voices

Currently only US English language is supported, with these voices:

* Paul (default)
* Betty
* Harry
* Frank
* Dennis
* Kit
* Ursula
* Rita
* Wendy

## Markup support

DECtalk phoneme markup is supported:
```ts
const textWithMarkup = `
	[:phoneme on]
	[sow<150,28>ay<150,28>wwey<300,37>kkih<150,37>nnth<20>uh<150,37>mor<200,33>nnihn<100,33>ae<150,33>nndday<150,33>ssteh<200,28>pp]
	[aw<300,28>ttssah<150,26>ay<150,25>ddae<200,25>nday<150,25>ttey<150,26>kkuh<150,26>ddiy<150,37>ppbr<20>eh<300,35>thae<300,33>]
	[ndgeh<300,35>ttrih<300,37>llhxay<300,33>ae<150,33>nnay<150,33>sk<150,33>rEy<150,33>m<150,33>_<150>tuh<150,33>tteh<150,33>ttaw<150,33>ppuh<150,33>]
	[ffmaa<200,33>lluh<300,33>nngs<150,35>_<150>wah<300,35>ssgow<150,35>ih<300,37>ngaw<450,33>nn<300,33>_<1200>]
	[ae<150,28>nnday<300,30>ssae<300,28>_<300>hxeh<750,37>ey<200,33>eh<750,33>ey<200,28>eh<750,28>ey<400,26>ey<400,25>_<100>]
	[hxeh<750,37>ey<200,33>eh<750,33>ey<200,26>eh<750,26>_<750>ay<150,35>sseh<200,37>hxeh<300,33>eh<300,30>_<1800>]
	[wwah<300,35>ttsgow<300,35>ih<400,37>nnaw<300,33>nn<90>]
`

const outputFileContent = await synthesize(textWithMarkup, {
	voice: DecTalkVoice.Betty,
	rate: 160,
})
```
