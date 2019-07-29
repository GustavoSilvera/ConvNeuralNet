#include "convneuralnet.h"



void convneuralnet::init(){
    y_scale = ofGetHeight() / num_networks;//divides the window width to the number of neural nets
    int largest_num_layers = 0;//the "num_layers" of the largest neural net
    for (int i = 0; i < num_networks; i++) {
        if (network[i].num_layers >= largest_num_layers) largest_num_layers = network[i].num_layers;
    }//simply finds the num_layers of the largest neural net
    read_data();
    for (int i = 0; i < num_networks; i++) {
        vec2 pos{ 100, y_scale * (i + 0.5) };//init x = 100, (i+0.5) to not start top neural net at VERY top of window
        network[i].init(pos, total_data, num_inputs);//create network[i]
        const int last_indx = network[i].num_layers - 1;//index of final layer (layers.size() - 1)
        layer last = network[i].layers[last_indx];//copy the last (output) layer of the network
        vec2 p{
            pos.x + largest_num_layers * network[i].diff + 200,//x position for 'ideals' neuron layer
            y_scale * (num_networks/2.0) - last.scale * ( last.num_neurons * (num_networks/2.0)) + last.scale*(i-1) * last.neuron_size
        };//divides evenly among the ypos based off number of neurons
        ideals.push_back(layer{ network[i].layers[network[i].num_layers - 1].num_neurons, p});
        ideals[i].init();
        //update last layer's position to be all in front of ideals
        network[i].layers[last_indx].update_pos(vec2{ p.x - 200, p.y });
        network[i].layers[0].update_pos(vec2{ pos.x, y_scale * (num_networks / 2.0) });
    }
}
const string kRootDir = "/home/gustavo/Documents/projects/openFrameworks/";
void convneuralnet::read_data(){
#define MAX_LINE 100
    std::ifstream file("../src/DATA_good.txt");//using CWD
    std::ifstream file2("../src/DATA_good.txt");//need this to find "file_length" bc the istreambuf iterator DELETES the file after reading??
    int file_length = int(std::count(std::istreambuf_iterator<char>(file2),std::istreambuf_iterator<char>(), '\n'));//gets number of '\n' in the file
    if(file.is_open()){
        int line_num = 0;
        while (line_num < file_length) {
            char line[MAX_LINE];//default line (less than 100 chars)
            file.getline(line, MAX_LINE);
            std::vector<double> ind_data;
            std::string sline = line;
            int end_inputs = sline.find(';');//has to be recomputed every time (strings are diff)
            int end_outputs = sline.size();
            int i = 0;
            num_inputs.push_back(0);//initialize num_inputs[line_num]
            num_outputs.push_back(0);//initialize num_outputs[line_num]
            while(sline.find(' ', i) < end_inputs){
                int next_space = sline.find(' ', i);//finds next instance of " " from index i
                string datum = sline.substr(i, next_space);
                ind_data.push_back(stod(datum));//adds all inputs to ind_data
                num_inputs[line_num]++;
                i = next_space + 1;//not get inf loop finding same index
            }
            i = end_inputs + 2;//refresh i with new start
            while(i < end_outputs){//space is IN FRONT of datum now... -_-
                int next_space = sline.find(' ', i);//finds next instance of " " from index i
                if(next_space == std::string::npos) next_space = end_outputs;//end of line
                string datum = sline.substr(i, next_space);
                ind_data.push_back(stod(datum));//adds all outputs to ind_data
                num_outputs[line_num]++;
                i = next_space+1;//not get inf loop finding same index
            }
            line_num++;
            total_data.push_back(ind_data);
        }
    }
    else cout << "Unable to open file" << std::getenv("CWD");
    file.close();
}
void convneuralnet::new_data(){
    for (int i = 0; i < num_networks; i++) {
        network[i].new_data(&ideals[i]);
    }
}

void convneuralnet::randomize_weights(){
    for (int i = 0; i < num_networks; i++) {
        network[i].randomize_weights();
    }
}

void convneuralnet::comp_avg_cost(){
    last_cost = avg_cost;
    avg_cost = 0;
    for (int i = 0; i < num_networks; i++) {
        network[i].comp_avg_cost(&ideals[i]);
        avg_cost += network[i].avg_cost;
    }
    avg_cost /= num_networks;
}

static void avg_improve_thread(net* network, layer* ideal){
    std::vector<double> v;
    network->avg_improve(ideal, ideal, v);
}
void convneuralnet::avg_improve(){
    std::vector<std::thread> threads;
    for(int i = 0; i < num_networks; i++){
        //threads.push_back(std::thread(avg_improve_thread, &network[i], &ideals[i]));
        threads.push_back(std::thread([&, i]{
            std::vector<double> v;
            network[i].avg_improve(&ideals[i], &ideals[i], v);
        }));
    }
    //for(int i = 0; i < num_networks; i++){
    //    threads[i].join();
    //}
    for (auto &thread:threads) {
        thread.join();
    }
        //std::thread top (network[0].avg_improve, &ideals[0], &ideals[0], v);
    /*for (int i = 0; i < num_networks; i++) {
       std::vector<double> v;
       network[i].avg_improve(&ideals[i], &ideals[i], v);
    }*/
    comp_avg_cost();
}
void convneuralnet::output(){
    std::ofstream output("output.txt");
    for (int i = 0; i < num_networks; i++) {
        output << "//Network: " << i + 1 << "\n";
        output << network[i].output();
    }
    output.flush();
}

void convneuralnet::draw()
{
    for (int i = 0; i < num_networks; i++) {
        network[i].draw();
        ideals[i].draw();
        drawFontText(network[i].cost, vec2(ideals[i].pos.x + 200, ideals[i].pos.y - 30));
        drawFontText(network[i].avg_cost, vec2(ideals[i].pos.x + 400, ideals[i].pos.y - 30));
    }
}
