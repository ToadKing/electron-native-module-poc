document.getElementById('reload').addEventListener('click', () => document.location.reload())

const { Example } = require('./native/build/Release/nativemodule')
const example = new Example(11);
console.log(example.value);
