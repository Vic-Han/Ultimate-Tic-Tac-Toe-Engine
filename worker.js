
let exports;
let memory;
let best;
let wasmMemory = new WebAssembly.Memory({initial: 256, maximum: 512});


runWasm = (move_list, list_size) => {
    
    var myArray = new Int32Array(memory.buffer)
	for(let a = 0; a < list_size; a++)
	{
		myArray[a] = move_list[a];
	}
	//console.log(gameInfo[0]);
    console.log(myArray,list_size)
	const move = best(0,list_size);
    
	console.log(move);
    return move;
} 


self.onmessage = event => {
    if(event.data.action === "fetchWebAssembly"){
        WebAssembly.instantiateStreaming(
            fetch("js_api.wasm"), {
                js: {
                    mem: wasmMemory
                }
            }
        ).then(results => {
            exports = results.instance.exports;
            memory = results.instance.exports.memory;
            best = results.instance.exports._Z12bestMoveListPii;
            self.postMessage({message: "Successfully saved Wasm"})
        }).catch(error => {
            self.postMessage({message: "Failed to Save Wasm", error: error})
        });
    }
    else if(event.data.action ==="computeMove"){
        const move = runWasm(event.data.moveList,event.data.listSize)
        self.postMessage({message:"Move Found",move:move})
    }
}