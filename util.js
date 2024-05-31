function convert(value) {
    if (value === 'X') { return 1 }
    return 2;
  }
  
  function miniBoardID(num) {
    const str = num.toString();
    return "mini" + str;
  }
  
  function squareID(num) {
    const str = num.toString();
    return "square" + str;
  }