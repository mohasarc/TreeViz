class GenericNode {
    /**
     * The constructor with
     * @param {An array or string of values to be added to the node} values 
     * @param {The x-value of the location of the node} x 
     * @param {The y-value of the location of the node} y 
     */
    constructor (values, x, y){
        if ((typeof values) == 'string')
            this.values = this.nodeParser(values);
        else
            this.values = values;
        this.children = [];
        this.x = x;
        this.y = y;
        this.width = 25; // The base width (for 1 digit item)
        this.BaseWidth = 25; // Constant (Read ONLY)
        this.updateWidth();
    }

    /**
     * Transforms a node string into node values array; the node string 
     * looks like the following: {val, val, val, .....}
     * @param {The string describing the node values} nodeStr 
     * @returns An array containing the values that go into the node
     */
    nodeParser(nodeStr){
        var values = [];
        var aVal = '';
        var nodeFilled = false;

        // If empty node
        if (nodeStr.substring(0, 2) == '{}')
            return [];

        nodeStr.split('').map(char => {
            // , means reached the end of one value
            // } means reached the end of the last value
            if ((char == ',' || char == '}') && !nodeFilled){
                values.push(aVal);
                aVal = '';
            }
            else {
                if (char != '{' && char != '}' && !nodeFilled){
                    aVal += char;
                    // console.log('adding to val', char, aVal);
                }
            }

            if (char == '}')
                nodeFilled = true;
        });

        // console.log('values from parser', values);
        return values;
    }

    /**
     * Returns an array of the value of the node
     */
    getValue(){
        return this.values;
    }

    /**
     * sets the values for the node
     * @param {An array of values for the node} values 
     */
    setValues(values){
        this.values = values;
        this.updateWidth();
    }

    /**
     * Returns all the children of the node
     */
    getChildren(){
        return this.children;
    }

    /**
     * adds children using an array of children to the node
     * @param {an array of children of the node} children 
     */
    setChildren(children){
        this.children = [...children];
    }

    /**
     * It adds a new value to the node
     * @param {The calue to be added} val 
     */
    addValue(val){
        this.values.push(val);
        this.updateWidth();
    }

    /**
     * It adds a new child to the node
     * @param {The child to be added to he node} child 
     */
    addChild(child){
        this.children.push(child);
    }

    /**
     * 
     * @param {The node's parent} parent 
     */
    setParent(parent){
        this.parent = parent;
    }

    /**
     * Returns the node's parent
     */
    getParent(){
        return this.parent;
    }

    /**
     * Gets the x-value of the node
     */
    getX(){
        return this.x;
    }

    /**
     * Gets the y-value of the node
     */
    getY(){
        return this.y;
    }

    /**
     * Setting the x-axis location of the node
     * @param {The x-axis value of the node} x 
     */
    setX(x){
        this.x = x;
    }

    /**
     * Setting the y-axis location of the node
     * @param {The y-axis value of the node} y
     */
    setY(y){
        this.y = y;
    }

    getLeftBound(){
        return this.x - (this.width/2);
    }

    getRightBound(){
        return this.x + (this.width/2);
    }

    setLeftBound(leftBound){
        this.x = leftBound + (this.width/2);
    }

    setRightBound(rightBound){
        this.x = rightBound - (this.width/2);
    }

    updateWidth(){
        var contentCount = 0;
        this.values.map(val=>{
            contentCount++;
        });

        this.width = this.BaseWidth * contentCount;
    }

    /**
     * This method draws the mode into p
     * @param {The p5 object} p 
     */
    draw(p){
        if (this.isEmpty())
            return;

        // Draw circles
        p.fill(255);
        p.ellipse(this.x, this.y, this.width, 25);

        // The values
        p.fill(0);
        var drawAt = this.getLeftBound() + 6;
        this.values.map((val, i) => {
            if (i < this.values.length - 1)
                p.text(val + ', ', drawAt, this.y + 5);
            else
                p.text(val , drawAt, this.y + 5);

            drawAt += (val+'                 ').length;
        });
    }

    /**
     * Determines whether a node is a leaf or not
     */
    isLeaf(){
        if (this.children.length == 0)
            return true
        return false;
    }

    /**
     * Empties the node
     */
    empty(){
        this.values = [];
    }

    /**
     * Evaluates whether node is empty
     */
    isEmpty(){
        return this.values.length == 0;
    }
}

export default GenericNode;