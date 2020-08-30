import React from 'react';
import Header from './header';
import Jumbotron from 'react-bootstrap/Jumbotron';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import ReactMarkdown from 'react-markdown'
import howTo from '../howTo.md'

class HowTo extends React.Component{
    constructor(props){
        super(props);
        this.canvasContainerRef = React.createRef();
        this.trees = [];
        this.state = { howtos: null }

        this.update = this.update.bind(this);
    }

    update(){
        this.canvasContainerRef.current.update();
    }
  
    componentWillMount() {
        fetch(howTo).then((response) => response.text()).then((text) => {
          this.setState({ howtos: text })
        })
      }    
      
    render(){
        return (
            <div>

                <Header/>
                <Jumbotron>
                    {/*
            //         <Row xs={12} md={12} lg={12}>
            //             <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
            //                 <h3> How to use TreeViz </h3>
            //             </Col>
            //         </Row>
            //         <br/>
            //         <Row xs={12} md={12} lg={12}>
            //             <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
            //                 There are multiple different ways to create a tree including: starting with and empty tree
            //                 and adding or removing values using + or - buttons, using tree string structure to describe a
            //                 particular tree then perform operations on it, and generating a random tree using random tree
            //                 generator by pressing Generate button. Here are the steps needed to perform the most common operations:
            //             </Col>
            //         </Row>
            //         <br/>

            //         <br/>
            //         <Row>
            //             <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
            //                 <h5>Generating random tree</h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Choose a tree type <br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Choose the range of numbers<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Choose the number of nodes wanted<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Click generate<br/>
            //                 </p><br/>

            //                 <h5>Building a tree:</h5>

            //                 <h6>&nbsp;&nbsp;&nbsp;&nbsp;1- By inserting numbers</h6>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Add the first number into tree description and press go<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Add other numbers into add a number text input and press +<br/>
            //                 </p>

            //                 <h6>&nbsp;&nbsp;&nbsp;&nbsp;2- By tree sequence</h6>

            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Enter a sequence of additions and deletions separated by commas<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Press GO<br/>
            //                 </p>

            //                 <h6>&nbsp;&nbsp;&nbsp;&nbsp;What is a tree sequence?</h6>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp; It is a sequence of comma-separated numbers that describe insertions and deletions that happened to the tree<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- To add an insertion into the sequence just add the number<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- To add a deletions into the sequence add letter 'd' before the number<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Ex: 1,2,9,10,d2,11,15,d10
            //                 </p>

            //                 <h6>&nbsp;&nbsp;&nbsp;&nbsp;3- By tree description string</h6>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Enter a tree string into 'Describe a tree' text field<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Press GO<br/>
            //                 </p>
            //             </Col>
            //         </Row>
            //         <Row>
            //             <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
            //                 <h6>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;What is tree string?  </h6>
            //             </Col>
            //         </Row>
            //         <Row>
            //             <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
            //                 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;It is a string that explains the tree such that:<br/>
            //                 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- numbers separated by commas and between {'{}'} belonges to the same node<br/>
            //                 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Each node's children are separated by commas and placed between ()<br/>
            //                 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Example tree string : {'{5,7}({3}{6}{8,9})'}<br/>
            //                 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Corresponding tree :
            //             </Col>
            //         </Row>
            //         <Row>
            //             <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"center"}}>
            //                 {'     {5,7}'}    <br/>
            //                 {' /     |     \\'}  <br/>
            //                 {'{3}   {6}   {8,9}'}<br/>
            //             </Col>
            //         </Row> <br/>
            //         <Row>
            //             <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>

            //                 <h5>Converting a tree into another type:</h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Click on use tree at the top right of the tree<br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Choose the target tree type <br/>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Click go<br/>
            //                 </p><br/>
            //                 <h5>View the tree in full screen</h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Click on []' <br/>
            //                 </p><br/>

            //                 <h5>Play the tree animation</h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Click on play button<br/>
            //                 </p><br/>

            //                 <h5>Stop tree animation</h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Click on stop button<br/>
            //                 </p><br/>

            //                 <h5>Zoom in the tree </h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Ctrl + scroll up<br/>
            //                 </p><br/>

            //                 <h5>Zoom out the tree </h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Ctrl + scroll down<br/>
            //                 </p><br/>

            //                 <h5>Fit the tree in the screen</h5>
            //                 <p>
            //                     &nbsp;&nbsp;&nbsp;&nbsp;- Click fit button<br/>
            //                 </p>
            //             </Col>
            //         </Row>

            */}         
            
            <Row xs={12} md={12} lg={12}>
                <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
                    <div style={{'text-align' : 'left'}}>
                        <ReactMarkdown source={this.state.howtos} />
                    </div>
                </Col>
            </Row>

                </Jumbotron>

                <footer className="blockquote-footer">
                This website was developped by <a href='https://github.com/mohasarc'>Mohammed S. Yaseen</a>
                </footer>
                <br/>
            </div>
        );
    }
}

export default HowTo;