import React from 'react'
import Canvas from './canvas'
import p5 from 'p5'
import GenericTree from '../models/GenericTree'

class DetachedCanvas extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            msg : 1,
            tree : new GenericTree()
        }
        this.recieveMessage = this.recieveMessage.bind(this);
        this.node = document.createElement('div');
        this.myP5 = new p5(this.Sketch, this.node);
        this.resize = this.resize.bind(this);
        this.handleZoom = this.handleZoom.bind(this);
    }

    
    Sketch = (p) => {
        p.width = 0;
        p.height = 0;
        p.tree = null;

        var cnv;

        p.setup = () => {
            cnv = p.createCanvas(p.width, p.height - 40);
            cnv.style('visibility: visible');
        }
   
        p.draw = () => {
            p.background('#34495e');
            if (p.tree){
                console.log('drawing the tree');
                p.scale(p.tree.getScale());
                p.tree.draw(p, p.width);
            }
        }

        p.createImage = () => {
            console.log('width', p.tree.getWidth(), 'height', p.tree.getHeight());
            var image = p.createGraphics(p.width, p.height);
            image.background('#34495e');
            image.scale(p.tree.getScale());
            p.tree.putInView(p.width/2);
            p.tree.draw(image,  p.width);
            image.save('img.png');
        }

        p.save = () => {
            p.saveCanvas(cnv, 'theTree', 'jpg');
        }

        p.scaleValue = 1;

        p.windowResized = (width, height) => {
            if (p.tree)
                p.tree.resize(width, true);
            p.resizeCanvas(width, height);
            p.redraw();
        }
    }

    componentDidMount(){
        window.addEventListener('message', this.recieveMessage, false);
        window.document.getElementById(this.state.msg).appendChild(this.node);
        window.addEventListener("resize", this.resize);
        // window.addEventListener('message', (e)=>{console.log(e)}, false);
    }

    resize(e){
        e.preventDefault();
        console.log(window.document);
        var treeWidth = this.state.tree.getWidth() + 0.2 * this.state.tree.getWidth();
        this.myP5.windowResized(treeWidth > window.innerWidth ? treeWidth : window.innerWidth  , window.innerHeight);
    }

    recieveMessage(e){
        console.log(e.data);
        console.log(e.source);
        console.log(e);
        this.setState((prevState)=>{
            console.log('set state called');
            prevState.tree.construct(e.data.tree.treeString);
            prevState.tree.setTreeType(e.data.tree.treeType);
            prevState.tree.setId(e.data.tree.id);
            prevState.tree.setScale(e.data.tree.scale);

            this.myP5.height = prevState.tree.getHeight();
            this.myP5.tree = prevState.tree;
            var treeWidth = prevState.tree.getWidth() + 0.2 * prevState.tree.getWidth();
            var treeHeight = prevState.tree.getHeight();
            this.myP5.width = treeWidth > window.innerWidth ? treeWidth : window.innerWidth;
            this.myP5.tree.center((treeWidth > window.innerWidth ? treeWidth : window.innerWidth)/2);
            this.myP5.windowResized(treeWidth > window.innerWidth ? treeWidth : window.innerWidth , treeHeight > window.innerHeight ? treeHeight : window.innerHeight);

            return {msg : e.data}
        });
    }

    handleZoom(e, value){
        console.log('width', this.state.tree.getWidth());
        var rect = e.target.getBoundingClientRect();
        // this.state.myP5.scaleValue = value/50;
        if (e.ctrlKey){
            e.preventDefault();
            this.state.tree.setScale(this.state.tree.getScale() - e.deltaY * 0.05);
            var treeWidth = this.state.tree.getWidth() + 0.2 * this.state.tree.getWidth();
            var treeHeight = this.state.tree.getHeight();
            this.myP5.width = treeWidth > window.innerWidth ? treeWidth : window.innerWidth;
            this.myP5.windowResized(treeWidth > window.innerWidth ? treeWidth : window.innerWidth , treeHeight > window.innerHeight ? treeHeight : window.innerHeight);
        }
    }

    render(){
        return (
            <div id={this.state.msg} onWheel={this.handleZoom} onClick={this.myP5.createImage}/>
            // this.state.tree.getTreeString() != '' 
            // ? <div id="theDiv" style={{'width':'9000'}}>
            //     {/* <Canvas
            //         topTree={false} popTree={null}
            //         key={this.state.tree.getId()} ref={this.state.child}
            //         tree={this.state.tree} 
            //         canvasNo={this.state.tree.getId()} 
            //         treeType={this.state.tree.getTreeType()}
            //         updateTreeOperations={null}
            //         theNode={this.node} p5={this.myP5} detached={true}/>  */}
            //     </div>
            // : <p>{'Loading...'}</p>
        );
    }
}

export default DetachedCanvas;