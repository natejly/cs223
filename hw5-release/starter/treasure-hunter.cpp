/*
 * treasure-hunte.cpp
 * CPSC 223 Pset 5
 *
 * TO STUDENT: Do not modify this file!
 *
 * Author: Alan Weide
 */

#include "LinkedList.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constants
const int FAIL = -1;

/**
 * Opens file islands_file, reads all islands found in that file, then adds
 *  them into the given LinkedList. Then it prints the list to outfile_name.
 *  Once finished it returns the number of islands inserted.
 *
 * @param isalnds_file name of the file from which to read in islands
 * @param outfile_name name of the file to which the islands should be printed
 * @param islands the LinkedList in which to store the islands read from
 *  input
 * @return the number of islands inserted.
 */
int readAllIslands(string islands_filename, string outfile_name, LinkedList &islands);

/**
 * Procedure that removes up to num_remove islands in an arbitrary pattern
 *  from the given LinkedList and prints the remaining islands of the list
 *  to outfile_name.
 *
 * @param outfile_name name of the file to which the list should be printed
 * @param islands the LinkedList from which to remove islands
 * @param num_remove the maximum number of removals to perform
 * @param pattern the pattern of "skips" to follow when removing
 * @return the number of islands removed
 * @result the list will be modified to have num_remove fewer islands according
 *  to the given pattern and the remaining islands will be printed to
 *  outfile_name
 */
int removeSome(string outfile_name, LinkedList &islands, int num_remove, vector<int> pattern);

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cerr << "Usage: " << argv[0] << " islands-file output-one output-two num-remove remove-pattern..." << endl;
        cerr << "Exiting." << endl;
        return 1;
    }

    const string islands_filename = argv[1];
    const string output_one_filename = argv[2];
    const string output_two_filename = argv[3];
    const int num_remove = stoi(argv[4]);

    LinkedList islands;

    // Read in all the islands and print
    int numIslands = readAllIslands(islands_filename, output_one_filename, islands);
    if (numIslands == FAIL)
    {
        cerr << "Failed to read and print all islands, exiting" << endl;
        return 1;
    }
    cout << "I just read and inserted " << numIslands << " islands" << endl;

    // Get rid of some of the islands
    vector<int> pattern;
    for (int i = 5; i < argc; i++)
    {
        pattern.push_back(stoi(argv[i]));
    }

    int removed = removeSome(output_two_filename, islands, num_remove, pattern);
    if (removed == FAIL)
    {
        cerr << "Failed to remove islands from list and write file,"
             << "exiting" << endl;
        return 1;
    }
    cout << "Removed " << removed << " islands and printed to file" << endl;

    cout << "Done!" << endl;

    return 0;
}

int readAllIslands(string islands_filename, string outfile_name, LinkedList &islands)
{
    int counter = 0;

    // Read in original list from file
    ifstream infile;
    infile.open(islands_filename.c_str());
    if (!infile.is_open())
    {
        cerr << "Could not add islands from file" << endl;
        return FAIL;
    }

    string islandInfo = "";
    while (getline(infile, islandInfo))
    {
        char accesschar = islandInfo[islandInfo.length() - 1];
        string island_name = islandInfo.substr(0, islandInfo.length() - 2);
        bool access = false;
        if (accesschar == 'Y')
        {
            access = true;
        }
        else
        {
            access = false;
        }
        Island is(island_name, access);
        islands.insertIsland(is);
        counter++;
    }

    infile.close();

    // Print the untouched list; it will be in reverse order than we inserted
    ofstream outfile;
    outfile.open(outfile_name.c_str());
    if (!outfile.is_open())
    {
        cerr << "Failed to open file for writing" << endl;
        return FAIL;
    }
    islands.print(outfile);
    outfile.close();
    return counter;
}

int removeSome(string outfile_name, LinkedList &islands, int num_remove, vector<int> pattern)
{
    int actual_removes = 0;
    for (int i = 0; i < num_remove; i++)
    {
        Island s = islands.getNextIsland();
        bool reached_end = false;
        for (int j = 1; j < pattern[i % (int)pattern.size()] && !reached_end; j++)
        {
            if (islands.isCurrPosNull())
            {
                reached_end = true;
                break;
            }
            s = islands.getNextIsland();
        }
        if (reached_end)
        {
            break;
        }

        islands.removeIsland(s);
        actual_removes++;

        if (islands.isCurrPosNull())
        {
            break;
        }
    }

    // Print the truncated list
    ofstream outfile;
    outfile.open(outfile_name.c_str());
    if (!outfile.is_open())
    {
        cerr << "Failed to open file for writing\n";
        return FAIL;
    }
    islands.print(outfile);
    outfile.close();
    return actual_removes;
}
