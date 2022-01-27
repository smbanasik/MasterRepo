## Description

This is an incomplete personal project made in C++ for the purpose of experimenting with classes and inheritance, while also developing a crafting system that is flexible, unique, and modular. 

The system would utilize tags created from the tag_class object to allow for flexbility with part requirements for finished products (such as using a wood or stone handle in a tool that just requires a "handle" tag). Additionally, the tags would determine statistics on the finished product, meaning there could be variety based off of the ingredients used.

Ingredients and products are subclasses of the item class. They are used to differentiate what an items purpose would be. The tagHandler_class contains functions that are used to create arrays of tags, get individual tags out of the arrays, and create smaller arrays from a master array.

The main function, found in Source.cpp, currently just tests out some functions, specifically the tag creation functions, item constructors, and checkHarvistability function.
