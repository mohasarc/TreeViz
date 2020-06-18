import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Button from 'react-bootstrap/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogTitle from '@material-ui/core/DialogTitle';
import InputLabel from '@material-ui/core/InputLabel';
import Input from '@material-ui/core/Input';
import MenuItem from '@material-ui/core/MenuItem';
import FormControl from '@material-ui/core/FormControl';
import Select from '@material-ui/core/Select';
import TextField from '@material-ui/core/TextField';

import FormGroup from '@material-ui/core/FormGroup';
import FormControlLabel from '@material-ui/core/FormControlLabel';
import Checkbox from '@material-ui/core/Checkbox';

const useStyles = makeStyles((theme) => ({
  container: {
    display: 'flex',
    flexWrap: 'wrap',
  },
  formControl: {
    margin: theme.spacing(1),
    minWidth: 120,
  },
}));

export default function DialogSelect(props) {
  var preferences = props.preferences;
  const treeTypes = {
    'binary' : 'BST',
    'twoThree' : '23T',
    'twoThreeFour' : '234',
    'b' : 'B-T',
    'avl' : 'VAL',
    'redBlack' : 'RBT',
  }
  
  const classes = useStyles();
  const [open, setOpen] = React.useState(false);
  const [order, setOrder] = React.useState(props.preferences.order);
  const [propagateSmallerValue, setPropagateSmallerValue] = React.useState(false);
  const [prioritizeInorderPredecessor, setPrioritizeInorderPredecessor] = React.useState(false);
  const [prioritizeRotateLeft, setPrioritizeRotateLeft] = React.useState(false);
  const [replaceWithPredecessor, setReplaceWithPredecessor] = React.useState(false);

  const handleOrderChange = (event) => {
    var value = Number(event.target.value);

    if (value >= 3)
      setOrder(value || '');
    else
      setOrder(3);
  }

  const handlePSVChange = (event) => {
    setPropagateSmallerValue(!propagateSmallerValue);
  };

  const handlePIPChange = (event) => {
    setPrioritizeInorderPredecessor(!prioritizeInorderPredecessor);
  };

  const handlePRLChange = (event) => {
    setPrioritizeRotateLeft(!prioritizeRotateLeft);
  };

  const handleRWPChange = (event) => {
    setReplaceWithPredecessor(!replaceWithPredecessor);
  };

  const handleClickOpen = () => {
    setOpen(true);
  };

  const handleClose = () => {
    setOpen(false);

    // restore values before change
    setOrder(preferences.order || '');
    setPropagateSmallerValue(preferences.propagateSmallerValue);
    setPrioritizeInorderPredecessor(preferences.prioritizeInorderPredecessor);
    setPrioritizeRotateLeft(preferences.prioritizeRotateLeft);
    setReplaceWithPredecessor(preferences.replaceWithPredecessor)
  };

  const handleOk = () => {
    setOpen(false);

    // Update the values
    preferences.order = order;
    preferences.propagateSmallerValue = propagateSmallerValue;
    preferences.prioritizeInorderPredecessor = prioritizeInorderPredecessor;
    preferences.prioritizeRotateLeft = prioritizeRotateLeft;
    preferences.replaceWithPredecessor = replaceWithPredecessor;
  };

  return (
    <div>
      <Button variant="outline-secondary" onClick={handleClickOpen} className='btn-block btn-sm'>Preferences</Button>
      
      <Dialog disableBackdropClick disableEscapeKeyDown open={open} onClose={handleClose}>
        <DialogTitle>{preferences.type.name} preferences</DialogTitle>
        <DialogContent>
          <form className={classes.container}>
            {
              preferences.type.value == treeTypes.twoThree || preferences.type.value == treeTypes.b ||
              preferences.type.value == treeTypes.twoThreeFour  
              ? 
              <div>
                <TextField
                  id="outlined-number"
                  label="Order"
                  type="number"
                  value={order}
                  disabled={preferences.type.value != treeTypes.b}
                  onChange={handleOrderChange}
                  InputLabelProps={{
                    shrink: true,
                  }}
                  variant="outlined"
                />
                <FormGroup col>
                  <FormControlLabel control={
                      <Checkbox
                        checked={propagateSmallerValue}
                        disabled={order % 2 != 0 }
                        onChange={handlePSVChange}
                        name="PSV"
                        color="primary"
                      />
                      }
                    label="Propagate smaller value"
                    />
                  <FormControlLabel control={
                      <Checkbox
                        checked={prioritizeInorderPredecessor}
                        onChange={handlePIPChange}
                        name="PIP"
                        color="primary"
                      />
                    }
                    label="Prioritize inorder predecessor"
                  />
                  <FormControlLabel control={
                      <Checkbox
                        checked={prioritizeRotateLeft}
                        onChange={handlePRLChange}
                        name="PRL"
                        color="primary"
                      />
                    }
                    label="Prioritize rotate left"
                  />
                </FormGroup>
              </div>
            : <div/>
            }

            {
              props.preferences.type.value == treeTypes.binary
              ? <FormControlLabel control={
                  <Checkbox
                    checked={replaceWithPredecessor}
                    onChange={handleRWPChange}
                    name="RWP"
                    color="primary"
                  />
                }
                label="While removing, replace with predecessor"
              />
              : <div/>
            }

          </form>
        </DialogContent>

        <DialogActions>
          <Button onClick={handleClose} style={{ width: 190}} variant="outline-secondary">
            Cancel
          </Button>
          <Button onClick={handleOk} variant="outline-secondary">
            Ok
          </Button>
        </DialogActions>
      </Dialog>
    </div>
  );
}