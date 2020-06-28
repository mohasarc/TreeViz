import React from 'react'
import p5 from 'p5'
import GenericTree from '../models/GenericTree'
import '../Styles/canvas.css'
import { withSnackbar } from 'notistack';
import { Slider } from 'rsuite';
import 'rsuite/dist/styles/rsuite-default.css';
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'

class DetachedCanvas extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            key : 1,
            tree : null,
            beingEnimated : false,
            speed : 1500,
        }

        document.body.style.overflow = "hidden";
        this.node = document.createElement('div');
        this.myP5 = null;
    }

    Sketch = (p) => {
        p.width = window.innerWidth;
        p.height = window.innerHeight;
        p.tree = null;
        var cnv;

        p.setup = () => {
            p.width = p.width < 200 ? 200 : p.width;
            cnv = p.createCanvas(p.width, p.height);
            cnv.style('visibility: visible');
        }
   
        p.draw = () => {
            p.background('#34495e');
            if (p.tree){
                p.translate(p.tree.tx, p.tree.ty);
                p.scale(p.tree.scale);
                p.tree.draw(p);
            } else {
                p.fill('FFFFF');
                p.textAlign(p.CENTER);
                p.textSize(20);
                p.text("NO TREE IS LOADED", p.width/2, p.height/2);
                p.textSize(12);
            }
        }

        p.scaleValue = 1;

        p.windowResized = (width, height) => {
            if (typeof height != 'undefined'){
                p.resizeCanvas(width, height);
                p.redraw();
            }
        }

        p.moveCamera = (deltaX, deltaY) => {
            // Update the current camera location
            p.tree.tx += deltaX;
            p.tree.ty += deltaY;
        }

        p.zoom = (scale, mouseX, mouseY) => {
            p.tree.scale = p.tree.scale * scale;
            p.tree.tx = mouseX * (1-scale) + p.tree.tx * scale;
            p.tree.ty = mouseY * (1-scale) + p.tree.ty * scale;
        }

        p.setTree = (tree) => {
            p.tree = tree;
            if (p.tree){
                p.tree.scale = 1;
                p.tree.tx = 0;
                p.tree.ty = 0;
            }
        }
    }

    componentDidMount(){
        window.addEventListener('message', this.recieveMessage, false);
        window.document.getElementById(this.state.key).appendChild(this.node);
        window.addEventListener("resize", this.resize);
        this.myP5 = new p5(this.Sketch, this.node);

        this.myP5.windowResized(window.innerWidth - 5, window.innerHeight - 5);
    }

    recieveMessage = (e) => {
        if (e.data != ''){
            this.state.tree = new GenericTree();
            this.state.tree.setTreeType(e.data.tree.treeType);
            this.state.tree.setId(e.data.tree.id);
            this.state.tree.setScale(e.data.tree.scale);
            this.state.tree.setSteps(e.data.tree.steps);
            this.state.tree.construct(e.data.tree.treeString);

            this.myP5.setTree(this.state.tree);

            this.myP5.windowResized(window.innerWidth - 5, window.innerHeight - 5);
            this.myP5.moveCamera((window.innerWidth - 5)/2, 50);

            this.setState((prevState)=>{
                return {key : e.data}
            });
        }
    }

    pressed = (e) => {
        this.mousePressed = true;
        if (e.touches){
            this.initialX = e.touches[0].clientX;
            this.initialY = e.touches[0].clientY;
        } else {
            this.initialX = e.clientX;
            this.initialY = e.clientY;
        }

        e.preventDefault();
    }

    released = (e) => {
        this.mousePressed = false;
        e.preventDefault();
    }

    dragged = (e) => {
        e.preventDefault();
        if (this.state.tree){
            if (this.mousePressed){
                // update initial values
                if (e.touches){
                    this.myP5.moveCamera((e.touches[0].clientX - this.initialX) * 0.5, (e.touches[0].clientY - this.initialY) * 0.5);

                    this.initialX = e.touches[0].clientX;
                    this.initialY = e.touches[0].clientY;
                } else {
                    this.myP5.moveCamera((e.clientX - this.initialX) * 0.5, (e.clientY - this.initialY) * 0.5);

                    this.initialX = e.clientX;
                    this.initialY = e.clientY;
                }
            }
        }
    }

    resize = () => {
        this.myP5.windowResized(window.innerWidth - 5, window.innerHeight - 5);
        this.setState((prevState) => {
            return {'key' : !prevState.key};
        });
        // if (this.state.tree){
        //     this.state.tree.center();
        // }
    }

    handleZoom = (e, value) => {
        if (this.state.tree){
            if (e.ctrlKey){
                this.myP5.zoom(e.deltaY < 0 ? 1.05 : 0.95, e.clientX, e.clientY);
            }
        }

        e.preventDefault();
    }

    treeToCenter = (e) => {
        if (this.state.tree){
            this.state.myP5.moveCamera((this.state.canvasRef.current.offsetWidth/2) - this.state.myP5.tree.tx, 50 - this.state.myP5.tree.ty);
            this.state.tree.setScale(1);
            e.preventDefault();
        }
    }
    
    playSteps = (e) => {
        if (this.state.tree){
            var i = 0;
            var immediatly = 1;
            this.setState({'beingEnimated' : true});
            this.state.tree.beingEnimated = true;
            var steps = this.state.tree.getSteps();
            var delay = 1500;

            (function loop() {
                if (!this.state.tree.beingEnimated){
                    i = steps.length; // skip ahead to the last step
                    immediatly = 0; // To stop immedietly without delay
                }

                // If steps were not empty
                if (i < steps.length){
                    if (steps[i].text != '')
                        this.props.enqueueSnackbar(steps[i].text);

                    if (steps[i].treeStr != ''){
                        this.state.tree.construct(steps[i].treeStr);
                        this.state.tree.setNote(steps[i].note);
                    }

                    // center needs to be called twice
                    this.state.tree.center();
                    this.state.tree.center();
                }

                if (i == steps.length - 1){
                    this.setState({'beingEnimated' : false});
                    this.state.tree.beingEnimated = false;
                    this.stopSteps();
                }

                if (++i < steps.length) {
                    setTimeout(loop.bind(this), this.state.speed * immediatly);  // call myself in 1 seconds time if required
                }
            }.bind(this))(); // above function expression is called immediately to start it off
        }
        e.preventDefault();
    }

    stopSteps = (e) => {
        if (this.state.tree){
            this.setState({'beingEnimated' : false});
            this.state.tree.beingEnimated = false;

            if (e){
                var steps = this.state.tree.getSteps();
                this.state.tree.construct(steps[steps.length - 1].treeStr);
                this.state.tree.setNote('');

                // center needs to be called twice
                this.state.tree.center();
                this.state.tree.center();
                e.preventDefault();
            }
        }
    }

    handleSlider = (value) => {
        // this.setState({speed : Number(e.target.value)});
        console.log(value);
        value = 3000 - ( value / 100 * 3000 );
        this.state.speed = value;
    }

    render(){
        return (
            <div>
                <div className='float-right' style={{height : 25, width : 100, 'position': 'absolute', 'top': '5px', 'right': '70px'}}>
                        <Slider defaultValue={50} tooltip={false} style={{'margin-bottom' : '0.5em', 'margin-top' : '0.5em'}} onChange={this.handleSlider}/>
                </div>
                        <div className='float-right' style={{height : 25, 'position': 'absolute', 'top': '5px', 'right': '5px'}}> 
                            <a key={this.state.beingEnimated} href='#' className='badge badge-light'  
                                onClick={this.state.tree && !this.state.tree.beingEnimated?this.playSteps:this.stopSteps}
                                style={{'margin-right':'0.5em'}}>
                                <div className={this.state.tree && !this.state.tree.beingEnimated?'play':'stop'} style={{'color' : '#FFFFFF'}}></div>
                            </a>
                            <a href='#' className='badge badge-light'  onClick={this.treeToCenter}
                                style={{'margin-right':'0.5em'}}>
                                <div className='center' style={{'color' : '#FFFFFF'}} ></div>
                            </a>
                        </div>

                <div>
                    <div style={{'background-color' : '#34495e' , 'height' : window.innerHeight}} 
                    id={this.state.key}
                    onTouchStart={this.pressed} onMouseDown={this.pressed} 
                    onTouchMove={this.dragged} onMouseMove={this.dragged} 
                    onTouchEnd={this.released} onMouseUp={this.released}
                    onWheel={this.handleZoom} 
                    />
                </div>
            </div>
        );
    }
}

export default withSnackbar(DetachedCanvas);