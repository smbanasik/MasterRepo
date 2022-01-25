// Name: Spencer Banasik
// NetID: SMB200007
package Editor;

import MyImplementations.MyArrayList;
import MyImplementations.MyArrayListStack;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Editor {
  /** cursor row position */
  int row;
  /** cursor column position */
  int col;
  /** the text of the editor */
  MyArrayList<String> text;
  /** the undo stack */
  MyArrayListStack<EditorAction> undoStack;
  /** the redo stack */
  MyArrayListStack<EditorAction> redoStack;
  
  String fileName;
  boolean isUndoAction;

  class EditorAction {
    /** the row of the action */
    int row;
    /** the column of the action */
    int col;
    /** the text of the action */
    String text;
    /** the action type */
    ActionType type;
  }

  enum ActionType {
    /** insert action */
    INSERT,
    /** delete action */
    DELETE,
    /** replace action */
    REPLACE
  }
  


  /**
   * Constructor
   */
  Editor(String fileName) {
	this.fileName = fileName;
	undoStack = new MyArrayListStack<EditorAction>();
	redoStack = new MyArrayListStack<EditorAction>();
    open(fileName);
  }

  /**
   * Open the file with the given name and read the contents into the editor.
   */
  void open(String fileName) {
    // read the file into the text
    // set the cursor to the beginning of the file
	  
	  //Set inputted file name to object file name
	  this.fileName = fileName;
	  
	  //initialize text and line for reader
	  text = new MyArrayList<String>();
	  String inputLine;
	  // converts filename string to path
	  Path path = Paths.get(fileName);
	  Charset cs = Charset.forName("US-ASCII");
	  //Buffered reader better for reading files instead of scanner
	  // new buffered reader takes path and charset
	  // Try to open file
	  try (BufferedReader fileInput = Files.newBufferedReader(path, cs)) {
		  
		  
		  // While it has a next line, input the element into the array list
		  // In the case of a scanner object, has next line could be used, but bufferedReader does not support that
		  // Instead set the line equal to the input of the buffered reader, and run while not null
		  while((inputLine = fileInput.readLine()) != null) {
			  
			  // Add the string into the text
			  text.add(inputLine);
			  
		  }
		  
		  // Initialize cursor position to beginning
		  row = 0;
		  col = 0;
		  
	  } catch (IOException error) {
		  
		  System.out.println("An error occured");
		  error.printStackTrace();
	  }
  }
  /**
   * Save the current text to currently open file.
   */
  void save() {
    // DONE
	  
	  saveAs(this.fileName);
	  
  }

  /**
   * Save the current text to the given file.
   */
  void saveAs(String fileName) {
	  
	  // set new file name to current one
	  this.fileName = fileName;
	  Charset cs = Charset.forName("US-ASCII");
	  Path path = Paths.get(fileName);
	  
	  try (BufferedWriter writer = Files.newBufferedWriter(path,  cs)) {
		  
		  for(String outputString : text) {
			  
			  writer.write(outputString);
			  writer.newLine();
			  
		  }
		  	
	  } catch (IOException error) {
		  
		  System.out.println("An error occured");
		  error.printStackTrace(); 
		  
	  }
	  
  }

  /**
   * Undo the last action.
   */
  void undo() {
    
	  // Change variable to prevent undo actions from appearing in undo stack
	  isUndoAction = true;
	  // Pop out most recent action and assign it to recentAction
	  EditorAction recentAction = undoStack.pop();
	  // move cursor in position
	  moveCursor(recentAction.row, recentAction.col);
	  // determine action type and counteract the action made
	  switch (recentAction.type) {
	  
		  case INSERT:
			  delete(recentAction.text.length());
			  break;
		  case DELETE:
			  insert(recentAction.text);
		  case REPLACE:
			  undo();
			  undo();
			  break;
	  }
	  
	  redoStack.push(recentAction);
	  isUndoAction = false;
  }

  /**
   * Redo the last undone action.
   */
  void redo() {
	  
	  // Since the action is already being pushed back onto the undo stack, this is necessary to prevent looping
	  isUndoAction = true;
	  EditorAction recentAction = redoStack.pop();
	  undoStack.push(recentAction);
	  moveCursor(recentAction.row, recentAction.col);
	  switch(recentAction.type) {
	  
	  case INSERT:
		  insert(recentAction.text);
		  break;
	  case DELETE:
		  delete(recentAction.text.length());
	  case REPLACE:
		  redo();
		  redo();
		  break;
	  }
	  
	  isUndoAction = false;
  }

  /**
   * Insert the given string at the current cursor position.
   * The cursor position is updated to point to the end of the inserted string.
   */
  void insert(String s) {
	String editorLine = text.get(row);
	text.set(row,  editorLine.substring(0,col) + s + editorLine.substring(col));
	
	//update cursor
	col += s.length();
	
	if (isUndoAction == false) {
		EditorAction undo = new EditorAction();
		undo.row = this.row;
		undo.col = this.col;
		undo.type = ActionType.INSERT;
		undo.text = s;
		undoStack.push(undo);
	}
  }
  /**
   * Delete n characters at the current cursor position.
   * The cursor position is updated to point to the end of the deleted string.
   */
  void delete(int n) {
	  
	  String editorLine = text.get(row);
	  String textDeleted = editorLine.substring(col, col+n);
	  text.set(row, editorLine.substring(0, col) + editorLine.substring(col + n));
	  
	  if (isUndoAction == false) {
		  EditorAction undo = new EditorAction();
		  undo.row = this.row;
		  undo.col = this.col;
		  undo.type = ActionType.INSERT;
		  undo.text = textDeleted;
		  undoStack.push(undo);
	  }
  }

  /**
   * Replace the n characters at the current cursor position with the given string.
   * The cursor position is updated to point to the end of the replaced string.
   */
  void replace(int n, String s) {
	  
	  delete(n);
	  insert(s);
	  if (isUndoAction == false) {
		  
		  EditorAction undo = new EditorAction();
		  undo.row = this.row;
		  undo.col = this.col;
		  undo.type = ActionType.REPLACE;
		  undo.text = s;
		  undoStack.push(undo);
	  }
	  
  }

  /**
   * Find the first instance of given string in the editor and set the cursor to
   * that position.
   */
  int[] find(String s) {
	  
	  //Scan through all of text
	  for (int i = 0; i < text.size(); i++) {
		  
		  // If the string returned in row i returns an index of string s, it exists on that row
		  if(text.get(i).indexOf(s) >= 0) {
			  
			  // Set row to selected row and column to first instance of string
			  row = i;
			  col = text.get(i).indexOf(s);
			  
			  return new int[] {row, col};
			  
		  }
	  }
	  
    return null;
  }
  
  /**
   * Move the cursor to the given position.
   */
  void moveCursor(int row, int col) {
	  
	  this.row = row;
	  this.col = col;
	  
  }

  /**
   * Return the current cursor position.
   */
  int[] getCursor() {
    return new int[] {row, col};
  }
  
  String getText(int row) {
	  
	  return text.get(row);
  }
  
  String getText(int row, int col) {
	  
	  return text.get(row).substring(col);
  }
  
  String getText(int row, int col, int n) {
	  
	  return text.get(row).substring(col, col + n);
  }

}