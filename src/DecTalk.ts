import { wrapEmscriptenModuleHeap } from 'wasm-heap-manager'

export async function synthesize(text: string, options: DecTalkOptions) {
	options = { ...defaultDecTalkOptions, ...options }

	const m = await getWasmModule()

	const manager = wrapEmscriptenModuleHeap(m)

	const outFilenameRef = manager.allocNullTerminatedUtf8String('out.wav')
	const textRef = manager.allocNullTerminatedUtf8String(text)

	const exitCode = await m._synthesize(textRef.address, outFilenameRef.address, options.voice, options.rate)

	outFilenameRef.free()
	textRef.free()

	if (exitCode !== 0) {
		throw new Error(`'synthesize' exited with a code of ${exitCode}`)
	}

	const outputFileContent = m.FS.readFile('out.wav')

	return outputFileContent
}

let wasmModule: any

async function getWasmModule() {
	if (wasmModule) {
		return wasmModule
	}

	const { default: initializer } = await import('../wasm/dectalk.js')

	wasmModule = await initializer()

	return wasmModule
}

export enum DecTalkVoice {
	Paul = 0,
	Betty = 1,
	Harry = 2,
	Frank = 3,
	Dennis = 4,
	Kit = 5,
	Ursula = 6,
	Rita = 7,
	Wendy = 8,
}

export const defaultDecTalkOptions: DecTalkOptions = {
	voice: DecTalkVoice.Paul,
	rate: 150,
}

export interface DecTalkOptions {
	voice?: DecTalkVoice
	rate?: number // Speaking rate in words per. Between 50 and 600.
}
