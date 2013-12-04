/* Snap_index.h
 * Group: Chris Findeisen, Martin Fracker, Daniel Frazee
 * Keeps track of Snap_picture objects via an index file
 */

#ifndef SNAP_INDEX_DEFINED // include guard
#define SNAP_INDEX_DEFINED

#include <boost/filesystem.hpp>
#include "Snap_facilities.h"
#include "Snap_picture.h"

namespace Snap {
	const string image_dir = "images/";
	const vector<string> tags { "Aggieland", "Pets", "Family", "Friends", "Vacation" };
}

// singleton pattern
class Snap_index {
public:
	// to be thrown as errors
	class Bad_format : public exception { 
	public:
		virtual const char* what() { return "index file: unable to parse the index file"; }
	};
	
	class Invalid_filename : public exception {
	public:
		virtual const char* what() { return "index file: no picture with that filename"; }
	};

	static Snap_index& get_instance() {
		static Snap_index instance("index.sif");
		return instance;
	}
		
	// each picture is saved individually to an index file
	void save_picture(const Snap_picture& pic);
	
	// the index file is translated all at once at the
	// start of the program
	void parse_index(); // translate the index file into Snap_picture objects
	Snap_picture find_by_filename(string fname); // returns the picture with the given filename
	int get_index_of(const Snap_picture& pic); // returns the index of the picture in the pictures vector
	vector<Snap_picture> find_all_with_tags(vector<string> tags); // returns a list of pictures with a given combination of tags
	
	// public getters
	Snap_picture get_picture(unsigned int i) const { return pictures[i]; } // once parsed, picture objects can be accessed from this vector
	int get_picture_count() const { return pictures.size(); } // how many pictures there currently are
	vector<Snap_picture> get_pictures() const { return pictures; } // we might need access to the whole vector at once (e.g. copy construct)
	void remove_picture(int i); // removes picture both from the pictures vector and from the index file

	// disable copy constructor and copy assignment
	Snap_index(const Snap_index&) = delete; 
	Snap_index& operator=(const Snap_index&) = delete;

private:
	// fname is the name of the index file that will be loaded
	Snap_index(string fname) :filename(fname) { 
		boost::filesystem::create_directory(Snap::image_dir);
		parse_index(); 
	}

	void rebuild_index(); // replaces the index file with a new index file containing all Snap_picture objects in pictures vector
	vector<Snap_picture> pictures; 
	string filename;
	void add_picture(const Snap_picture& pic);
	
	// static constants: tokens
	static const char SEPARATOR;
	static const string NO_TAG;
};

#endif // SNAP_INDEX_DEFINED