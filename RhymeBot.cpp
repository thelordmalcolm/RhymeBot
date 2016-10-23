#include "RhymeBot.h"
#include <iostream>


/** Inserting Words **/

void RhymeBot::insertWithPronunciation(string word, vector<Sound> pronunciation) {

    WordUtilities w;
    w.setSound(pronunciation);

    mw.insert(make_pair(word, w));

    // The following lines should be removed. They are here to show what is being added to you data structures
//    cout << word << ": ";
//    for(int i=0; i<pronunciation.size(); i++){
//        cout << pronunciation.at(i) << " ";
//    }
//    cout << endl;

}

void RhymeBot::addPartOfSpeech(string word, PART_OF_SPEECH partOfSpeech) {
    map<string, WordUtilities>::iterator it;
    it = mw.find(word);

    if (it != mw.end()) {
        it->second.setPOS(partOfSpeech);
    }

    // The following line should be removed. They are here to show what is being added to you data structures
//    cout << word << ": " << partOfSpeech << endl;

}


/** Helper Functions **/

// returns the number of syllables in word
int RhymeBot::countSyllables(string word) {
    std::map<string, WordUtilities>::iterator it;
    it = mw.find(word);
    vector<Sound> sounds;
    int count = 0;
    if (it != mw.end()) {
        sounds = it->second.getSound();
        for (int i = 0; i < sounds.size(); i++) {
            if (sounds.at(i).isVowel()) {
                count++;
            }
        }
    }
    return count;
}

// returns the number of rhyming syllables in the two words. This is defined as the number of vowel sounds in the
//  largest rhyming suffix.
//
// Words are considered a rhyme if they have the same last vowel sound as well as the same sounds following
//  the last vowel. Note: These are syllabic rhymes since the matching vowels might not be stressed
int RhymeBot::rhymingSyllables(string word1, string word2) {
    std::map<string, WordUtilities>::iterator it;
    it = mw.find(word1);
    std::map<string, WordUtilities>::iterator it2;
    it2 = mw.find(word2);
    vector<Sound> sound1, sound2;
    if (it != mw.end()) {
        sound1 = it->second.getSound();
    }
    if (it2 != mw.end()) {
        sound2 = it2->second.getSound();
    }
    int syllables = 0;
    for (int i = sound1.size() - 1, j = sound2.size() - 1; i >= 0 && j >= 0; i--, j--) {
        if (sound1.at(i) == sound2.at(j)) {
            if (sound1.at(i).isVowel()) {
                syllables++;
            }
        }
        else {
            break;
        }
    }
    return syllables;
}

// returns the number of identical sounds in the largest matching prefix of the two words.
//
// Words are considered an alliteration if they have the same first sound
int RhymeBot::alliterationSounds(string word1, string word2) {
    // TODO
    std::map<string, WordUtilities>::iterator it;
    it = mw.find(word1);
    std::map<string, WordUtilities>::iterator it2;
    it2 = mw.find(word2);
    vector<Sound> sound1, sound2;
    if (it != mw.end()) {
        sound1 = it->second.getSound();
    }
    if (it2 != mw.end()) {
        sound2 = it2->second.getSound();
    }
    int alliterations = 0;
    for (int i = 0, j = 0; i < sound1.size() && j < sound2.size(); i++, j++) {
        if (sound1.at(i) == sound2.at(j)) {
            alliterations++;
        }
        else {
            break;
        }
    }
    return alliterations;
}


/** Search for Rhymes and Alliterations **/

// returns all words that rhyme at least 1 syllable with the input word
// returns the empty vector if no rhymes are found or if the given word is not in the dictionary
vector<string> *RhymeBot::getAllRhymes(string word) {
    vector<string> *rhymingWords = new vector<string>;

    std::map<string, WordUtilities>::iterator it;
    for (it = mw.begin(); it != mw.end(); it++) {
        if (rhymingSyllables(word, it->first) > 0 && word != it->first) {
            rhymingWords->push_back(it->first);
        }
    }
    return rhymingWords;
}

// returns all words that form an alliteration of at least 1 sound with the input word
// returns the empty vector if no rhymes are found or the given word is not known
vector<string> *RhymeBot::getAllAlliterations(string word) {
    vector<string> *alliterationWords = new vector<string>;
    // TODO
    std::map<string, WordUtilities>::iterator it;
    for (it = mw.begin(); it != mw.end(); it++) {
        if (alliterationSounds(word, it->first) > 0 && word != it->first) {
            alliterationWords->push_back(it->first);
        }
    }
    return alliterationWords;
}


/** Finding the Perfect Word **/

// returns the best word with the specified number of syllables and part of speech that rhymes with the given word.
// Best is defined by the maximum number of rhyming syllables.
string RhymeBot::findBestRhyme(int numberOfSyllables, string rhymesWith) {
    vector<string> *allRhymingWords = getAllRhymes(rhymesWith);
    string bestRhyme = "";
    int counter = 0;

    for (int i = 0; i < allRhymingWords->size(); i++) {
        string word = allRhymingWords->at(i);
        if (countSyllables(word) == numberOfSyllables) {
            int rsyllables = rhymingSyllables(word, rhymesWith);
            if (rsyllables > counter) {
                counter = rsyllables;
                bestRhyme = word;
            }
        }
    }

    return bestRhyme;
}

string RhymeBot::findBestRhyme(PART_OF_SPEECH partOfSpeech, string rhymesWith) {
    // TODO
    vector<string> *allRhymingWords = getAllRhymes(rhymesWith);
    string bestRhyme = "";
    int counter = 0;

    for (int i = 0; i < allRhymingWords->size(); i++) {
        std::map<string, WordUtilities>::iterator it;
        string word = allRhymingWords->at(i);
        it = mw.find(word);

        if (it != mw.end()) {
            PART_OF_SPEECH p = it->second.getPOS();
            if (p == partOfSpeech) {
                int rsyllables = rhymingSyllables(word, rhymesWith);
                if (rsyllables > counter) {
                    counter = rsyllables;
                    bestRhyme = word;
                }
            }
        }
    }
    return bestRhyme;
}

string RhymeBot::findBestRhyme(int numberOfSyllables, PART_OF_SPEECH partOfSpeech, string rhymesWith) {
    // TODO
    vector<string> *allRhymingWords = getAllRhymes(rhymesWith);
    string bestRhyme = "";
    int counter = 0;

    for (int i = 0; i < allRhymingWords->size(); i++) {
        std::map<string, WordUtilities>::iterator it;
        string word = allRhymingWords->at(i);
        it = mw.find(word);

        if (it != mw.end()) {
            PART_OF_SPEECH p = it->second.getPOS();
            if (countSyllables(word) == numberOfSyllables) {
                if (p == partOfSpeech) {
                    int rsyllables = rhymingSyllables(word, rhymesWith);
                    if (rsyllables > counter) {
                        counter = rsyllables;
                        bestRhyme = word;
                    }

                }
            }
        }

    }


    return bestRhyme;
}

// returns the best word with the specified number of syllables and part of speech that forms an alliteration with
// the given word. Best is defined by the number of maximum number of alliterating sounds.
string RhymeBot::findBestAlliteration(int numberOfSyllables, string alliterationWith) {
    // TODO
    vector<string> *allAlliterationWord = getAllAlliterations(alliterationWith);
    string bestAlliteration = "";
    int counter = 0;

    for (int i = 0; i < allAlliterationWord->size(); i++) {
        string word = allAlliterationWord->at(i);

        if (countSyllables(word) == numberOfSyllables) {
            int rsyllables = alliterationSounds(word, alliterationWith);
            if (rsyllables > counter) {
                counter = rsyllables;
                bestAlliteration = word;
            }
        }
    }

    return bestAlliteration;
}

string RhymeBot::findBestAlliteration(PART_OF_SPEECH partOfSpeech, string alliterationWith) {
    // TODO
    vector<string> *allAlliterationWord = getAllAlliterations(alliterationWith);
    string bestAlliteration = "";
    int counter = 0;

    for (int i = 0; i < allAlliterationWord->size(); i++) {
        std::map<string, WordUtilities>::iterator it;
        string word = allAlliterationWord->at(i);
        it = mw.find(word);

        if (it != mw.end()) {
            PART_OF_SPEECH p = it->second.getPOS();
            if (p == partOfSpeech) {
                int rsyllables = alliterationSounds(word, alliterationWith);
                if (rsyllables > counter) {
                    counter = rsyllables;
                    bestAlliteration = word;
                }
            }
        }
    }
    return bestAlliteration;
}

string RhymeBot::findBestAlliteration(int numberOfSyllables, PART_OF_SPEECH partOfSpeech, string alliterationWith) {
    // TODO
    vector<string> *allAlliterationWord = getAllAlliterations(alliterationWith);
    string bestAlliteration = "";
    int counter = 0;

    for (int i = 0; i < allAlliterationWord->size(); i++) {
        std::map<string, WordUtilities>::iterator it;
        string word = allAlliterationWord->at(i);
        it = mw.find(word);

        if (it != mw.end()) {
            PART_OF_SPEECH p = it->second.getPOS();
            if (countSyllables(word) == numberOfSyllables) {
                if (p == partOfSpeech) {
                    int rsyllables = alliterationSounds(word, alliterationWith);
                    if (rsyllables > counter) {
                        counter = rsyllables;
                        bestAlliteration = word;
                    }

                }
            }
        }

    }


    return bestAlliteration;
}

// Combine findBestRhyme and findBestAlliteration. Best is defined by the sum of the number of rhyming syllables
//  and the number of alliterating sounds.
string RhymeBot::findPerfectWord(int numberOfSyllables, PART_OF_SPEECH partOfSpeech, string rhymesWith,
                                 string alliterationWith) {
    // TODO
    vector<string> *allAlliterationWord = getAllAlliterations(alliterationWith);
    string bestAll = "";

    int counter = 0;
    for (int i = 0; i < allAlliterationWord->size(); i++) {
        std::map<string, WordUtilities>::iterator it;
        string word = allAlliterationWord->at(i);
        it = mw.find(word);

        if (it != mw.end()) {
            PART_OF_SPEECH p = it->second.getPOS();

            if (p == partOfSpeech) {
                if (alliterationWith != it->first) {
                    if (countSyllables(word) == numberOfSyllables) {
                        if (rhymesWith != it->first) {
                            int rsyllables = alliterationSounds(it->first, alliterationWith);
                            int bsyllables = rhymingSyllables(it->first, rhymesWith);
                            int equal = rsyllables + bsyllables;
                            if (equal > counter && rsyllables > 0 && bsyllables > 0) {
                                counter = equal;
                                bestAll = word;
                            }
                        }
                    }
                }
            }
        }
    }


    return bestAll;
}
