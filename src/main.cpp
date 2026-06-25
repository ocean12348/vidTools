#include <iostream>
#include <string>

struct Options
{
    std::string inputFile;
    std::string outputFile;
    std::string format;
    bool compress = false;
    int quality = 23;           // compression quality
    bool targetSize = false;    // whether the user wants to target a size
    float targetSizeMB = 0.0f;  // the target size in MB
    
};

//try and find the output thingamabob
        //Grab it and do rfind on it to get the last dot
        //return the place of that dot
        //return everything after that dot
std::string detectFormat(std::string filename)
{
    size_t dotPos = filename.rfind('.');
    if(dotPos != std::string::npos)
    {
        return filename.substr(dotPos+1);
    }
    else return "";
}

Options parseArgs(int argc, char* argv[])
{
    Options opts;

    for(int i=1; i < argc; i++)
    {
        std::string arg = argv[i];

        if(arg == "--input" && i+1 < argc){
            opts.inputFile = argv[++i];
        }
        else if(arg == "--output" && i+1 < argc){
            opts.outputFile = argv[++i];
        }
        else if(arg == "--format" && i+1 < argc){
            opts.format = argv[++i];
        }
        else if(arg == "--compress"){
            opts.compress = true;
        } 
        else if(arg == "--quality" && i+1 < argc){
            opts.quality = std::stoi(argv[++i]);
        }
        else if(arg == "--tgtSize"){
            if(i+1 < argc){
                opts.targetSize = true;
                opts.targetSizeMB = std::stof(argv[++i]);
            }
            else std::cout << "Error: No target size specified. \nPlease enter a valid number in MB \nExample: --tgtSize 10";
        }
    }

    if(opts.format.empty() && !opts.outputFile.empty())
    {
        opts.format = detectFormat(opts.outputFile);
    }
    if(opts.format.empty())
    {
        std::cout << "An error has occured! Please enter an output format or enter a filename for the output file. \n";
    }
    
    return opts;
}

void convertVideo(const Options& opts)
{

    std::string command = "ffmpeg -i " + opts.inputFile;
    if(opts.compress == true)
    {
        command += " -crf" + std::to_string(opts.quality);
    }
    command += " " + opts.outputFile;
    //Fixed
    std::cout << "Running: " << command << "\n";
    int result = std::system(command.c_str());
    if(result != 0)
    {
        std::cout << "Error: FFmpeg failed. \n";
    }
}

int getVidInfo(const Options& opts)
{
    std::string getVidInfoCommand = "ffmpeg -i " + opts.inputFile;
    std::cout << "Running: " << getVidInfoCommand << "\n";
    std::system(getVidInfoCommand.c_str());
    
    //now we gotta find the shi that is outputted
    FILE
}



int main(int argc, char* argv[])
{
    Options opts = parseArgs(argc, argv);
    std::cout << "vidTools: CLI Video processing tools. \n";
    if(opts.inputFile.empty())
    {
        std::cout << "Error: No input file. Use --input. \n";
        return 1;
    }
    if(opts.outputFile.empty())
    {
        std::cout << "Error: No output file. Use --output. \n";
        return 1;
    }

    convertVideo(opts);
    return 0;
}
