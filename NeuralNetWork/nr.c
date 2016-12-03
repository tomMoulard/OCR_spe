//madeby moular_b
#include "nr.h"

int xor(int a, int b)
{  //explicit content
    return (a*(b ? 0 : 1) || (a ? 0 : 1)*b) ? 1 : 0;
}
int nand(int a, int b)
{  //explicit content
    return a * b ? 0 : 1;
}

//ulitity
double sigmoid(double z)
{  //explicit content
    return 1.0 / (1.0 + exp(z));
}
double *sigmoidStar(double *z, int len)
{  //explicit content
    double *res = malloc(sizeof(double) * len);
    for (int i = 0; i < len; ++i)
    {
        res[i] = sigmoid(z[i]);
    }
    return res;
}
double sigmoidPrime(double z)
{  //explicit content
    return sigmoid(z) * (1 - sigmoid(z));
}
double dotdouble(double coeff, double *a, int len)
{  //do a dot mathematical function :3 coucou
    double res = 0;
    if (coeff == 0 || len == 0)
        return 0;
    //printf("dot : %f * (", coeff);
    for (int i = 0; i < len; ++i)
    {
        //printf("%f , ", a[i]);
        res += a[i] * coeff;
    }
    //printf(" ) = %f\n", res);
    return res;
}
double *append(double *a, double *b, int lenA, int lenB)
{  //To append two list a and b.
    double *res = malloc(sizeof(a) * lenA + sizeof(b) * lenB);
    res = a;
    for (int i = lenA; i < lenB; ++i)
    {
        res[i] = *b;
    }
    return res;
}
//########################prints#################################
void printArrayIntLen(int *array, int len)
{  //explicit content
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", array[i]);
    }
}

void printArrayIntEnd(int *beg, int *end)
{  //explicit content
    for(; beg < end; ++beg)
        printf("%d\n", *beg);
}
void printNetwork(Network net)
{  //explicit content
    int i, j;
    printf("#~~~~~~~~~~~ NETWORK ~~~~~~~~~~~#\n");
    printf("|lenlayers  : %d                 |\n", net.lenlayers);
    printf("|numLayers  :                   |\n|");
    for(i = 0; i < net.lenlayers; ++i)
    {
        printf("%d ", net.numLayers[i]);
    }
    printf("                         |\n|seed       : %ld        |\n",\
        net.seed);
    printf("|len        : %d                 |\n", net.len);
    printf("|lenbiases  : %d                 |\n", net.lenbiases);
    printf("|lenweight  : %d                 |\n", net.lenweight);
    printf("|size       :                   |\n|");
    printArrayIntLen(net.sizes, net.len);
    printf("                         |\n|biases     :                   |\n");
    int pos = 0;
    for(i = 0; i < net.lenlayers; ++i)
    {
        for (j = 0; j < net.numLayers[i]; ++j){
            printf("| %f", net.biases[pos]);
            pos += 1;
        }
        printf("|\n");
    }
    printf("|                               |\
        \n|weight     :                   |\n");
    for (int k = 0; k < net.lenweight; ++k)
    {
        printf("| %d :  %f |  %d  |\n", k, net.weight[k], net.lenweight);
    }
    printf("#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#\n");
}
void printNetworkArray(Network *a)
{
    while(a)
    {
        printNetwork(*a);
        a += 1;
    }
}
void printBashint(Bashint b)
{ //explicit content
    printf("#~~~~~~~~~~ Test ~~~~~~~~~#\n");
    printf("|res : %f            |\n|Input : ", b.res);
    int i = 0, j = 0;
    for (i = 0; i < 30; ++i)
    {
        for (j = 0; i < 30; ++i)
        {
        printf("%f ", b.input[i + j]);
        }
        printf("\n");
    }
    printf("|\n#~~~~~~~~~~~~~~~~~~~~~~~~~~#\n");
}
void printBashintArray(Bashint *a, int len)
{
    for (int i = 0; i < len; ++i)
    {
        printf(" Bashint n° %d\n", i);
        printBashint(a[i]);
    }
}
void printdoublearray(double *array)
{
    while(*array)
    {
        printf("%f ", *array);
        array = array + 1;
    }
}
Network makeNetWork(int len, int *sizes)
{ //To create a brand (and shiny) new NeuralNetwork
    Network net;
    //lenlayers
    net.lenlayers = 3;
    //numlayers
    net.numLayers = sizes;
    //lenbiases
    net.lenbiases = sizes[0];
    for (int i = 1; i < len; ++i)
    {
        net.lenbiases += sizes[i];
    }
    //len
    net.len   = len;
    //sizes
    net.sizes = sizes;
    //seed
    net.seed  = time(NULL);
    srand(net.seed);
    //*biases
    net.biases = malloc(sizeof(double) * net.lenbiases);
    for (int i = 0; i < net.lenbiases; ++i)
    {
        net.biases[i] = ((double)rand()/(double)RAND_MAX);
    }
    //lenweight
    //len first  = [0] * [1]
    //len second = [1] * [2]
    net.lenweight = 0;
    for (int i = 0; i < net.lenlayers - 1; ++i)
    {
        net.lenweight += net.numLayers[i] * net.numLayers[i + 1];
    }
    //*weight
    net.weight = malloc(sizeof(double) * net.lenweight);
    for (int j = 0; j < net.lenweight; ++j)
    {
        net.weight[j] = ((double)rand()/(double)RAND_MAX);
    }
    //lenweight
    return net;
}
void freeNetwork(Network net)
{  //explicit content
    free(net.sizes);
    free(net.weight);
    free(net.biases);
}
void freeBashint(Bashint b)
{ //explicit content
    free(b.input);
}
void freedouble2star(double **a, int len)
{
    for (int i = 0; i < len; ++i)
    {
        free(a[i]);
    }
    free(a);
}
Bashint *makeBAshXor(int len, Network net)
{   //create a bash of randomely generated XOR int *inputlist and int res;
    //reusable ti create random things ;)
    Bashint *res = malloc(sizeof(Bashint) * len);
    //initiate random
    srand(net.seed);
    for (int i = 0; i < len; ++i)
    {
        Bashint b;
        double *tmp = malloc(sizeof(double) * 2);
        *tmp = rand()%2;
        *(tmp + 1) = rand()%2;
        b.res = xor(*tmp, *(tmp + 1));
        b.input = tmp;
        res[i] = b;
    }
    //printBashintArray(res, len);
    return res;
}
Bashint *suffleBashint(Bashint *bash, int len, time_t seed)
{ //to shuffle all elts in the BashintArray
    srand(seed);
    int pos;
    Bashint tmp;
    for (int i = 0; i < len - 1; ++i)
    {
        pos = rand() % (len - i - 1);
        tmp = bash[len - i - 1];
        bash[len - i - 1] = bash[pos];
        bash[pos] = tmp;
    }
    return bash;
}
double *cutarray(double *array, int posmin, int posmax)
{
    //printf("cut : %d, %d\n", posmin, posmax);
    //printdoublearray(array);
    int len = posmax - posmin;
    double *res = malloc(sizeof(double) * len);
    for (int i = 0; i < len; ++i)
    {
        res[i] = array[i + posmin];
    }
    return res;
}
double **backprop(Network *network, double *x, double y) //may be done .....
{
    double **res = malloc(sizeof(double *) * 2);
    Network net = *network;
    //init:
    double *nabla_b = malloc(sizeof(double) * net.lenbiases);
    int i;
    for(i = 0; i < net.lenbiases; ++i)
    {
        nabla_b[i] = 0;
    }
    double *nabla_w = malloc(sizeof(double) * net.lenweight);
    for(i = 0; i <net.lenweight; ++i)
    {
        nabla_w[i] = 0;
    }
    //feedforward
    double *activation = x;
    int min_len =
        (net.lenbiases > net.lenweight ? net.lenweight : net.lenbiases);
    double **activations = malloc(sizeof(double *) * min_len);
    double *zs           = malloc(sizeof(double) * min_len);
    double z;
    int thisLayerWieght  = 0;
    int nbneuronsleft    = net.numLayers[0];
    int posmininweight   = 0;
    double *resT;
    for(i = 0; i < min_len - 1; ++i)
    {
        if(nbneuronsleft) // ==0
        {
            thisLayerWieght += 1;
            nbneuronsleft = net.numLayers[thisLayerWieght];
        }
        posmininweight += 1;
        resT = cutarray(net.weight, posmininweight,
            posmininweight + net.numLayers[thisLayerWieght]);
        z              = dotdouble(activation[i], resT, net.numLayers[thisLayerWieght]);
        z              += net.biases[i];
        nbneuronsleft  -= 1;
        zs[i]          = z;
        activation[i]  = sigmoid(z);
        activations[i] = activation;
    }
    double delta = (activations[0][min_len - 1] - y )
        * sigmoidPrime(zs[min_len - 1]);
    double sp;
    for (int l = 2; l < net.lenlayers; ++l)
    {
        z                    = zs[min_len - l];
        sp                   = sigmoidPrime(z);
        //no transposition : useless....
        delta                = dotdouble(delta, net.weight, net.lenweight - l - 1) * sp;
        nabla_b[min_len - l] = delta;
        nabla_w[min_len - l] = dotdouble(delta, activations[l],
            min_len - l - 1) * sp;
    }
    //building result
    res[0]   = nabla_b;
    res[1]   = nabla_w;
    //free
    *network = net;
    free(activations);
    free(zs);
    free(nabla_b);
    free(nabla_w);
    //I'm freeeee, from my worries
    return res;
}
Bashint *update_mini_bash(Bashint *mini_bash, size_t len_mini_bash,
    double eta, Network *network) //done
{
    Network net = *network;
    //initialization:
    double *nabla_b = malloc(sizeof(double) * net.lenbiases);
    int i;
    for (i = 0; i < net.lenbiases; ++i)
    {
        nabla_b[i] = 0;
    }
    double *nabla_w = malloc(sizeof(double) * net.lenweight);
    for (i = 0; i < net.lenweight; ++i)
    {
        nabla_w[i] = 0;
    }
    //loop
    Bashint b;
    double *x;
    double y;
    double **deltas = malloc(sizeof(double *) * 2);
    int j;
    size_t w;
    for (w = 0; w < len_mini_bash; ++w)
    {
        b = mini_bash[w];
        x = b.input;
        y = b.res;
        deltas = backprop(network, x, y);
        //deltas[0] == delta_nabla_b and deltas[1] == delta_nabla_w
        for(j = 0; j < net.lenbiases; ++j)
        {
            nabla_b[j] += deltas[0][j];
        }
        for(j = 0; j < net.lenweight; ++j)
        {
            nabla_w[j] += deltas[1][j];
        }
    }
    int k;
    for (k = 0; k < net.lenweight; ++k)
    {
        net.weight[k] = net.weight[k] - (eta / len_mini_bash) * nabla_w[k];
    }
    for(k = 0; k < net.lenbiases; ++k)
    {
        net.biases[k] = net.biases[k] - (eta / len_mini_bash) * nabla_b[k];
    }
    *network = net;
    //free
    free(nabla_b);
    free(nabla_w);
    //freeNetwork(net);
    return mini_bash;
}
double *feedforward(Network net, double *x)
{
    int min_len =
        (net.lenbiases > net.lenweight ? net.lenweight : net.lenbiases);
    for (int i = 0; i < min_len; ++i)
    {
        x[i] = sigmoid(dotdouble(net.weight[i], x, min_len) + net.biases[i]);
    }
    return x;
}
int argmax(double *array, int len)
{
    int res = 0;
    for (int i = 1; i < len; ++i)
    {
        if(array[i] > array[res])
            res = i;
    }
    return res;
}
double evaluate(Bashint *test_data, int len_test_data, Network net)
{
    double res = 0;
    double **test_result = malloc(sizeof(double *) * len_test_data);
    int min_len =
        (net.lenbiases > net.lenweight ? net.lenweight : net.lenbiases);
    //building test_result
    for (int i = 0; i < len_test_data; ++i)
    {
        test_result[i] = malloc(sizeof(double) * 2);
        test_result[i][0] = (double)argmax(feedforward(net,
            test_data[i].input), min_len);
        test_result[i][1] = test_data[i].res;
    }
    //compute test_result
    for (int i = 0; i < len_test_data; ++i)
    {
//printf("evaluate : x = %f et y = %f\n", test_result[i][0], test_result[i][1]);
        if (test_result[i][0] + 97 == test_result[i][1])
            res += 1;
    }
    freedouble2star(test_result, len_test_data);
    return res;
}
Bashint *cutarrayBashint(Bashint *b, int posmin, int posmax)
{
    int len = posmax - posmin;
    Bashint *res = malloc(sizeof(Bashint) * len);
    for (int i = 0; i < len; ++i)
    {
        res[i] = b[i + posmin];
    }
    return res;
}
Network SGD(Network net, Bashint *training_data, size_t len_training_data,
    int epoch, int mini_bash_size, double eta, Bashint *test_data,
    size_t len_test_data)//V2
{
    size_t n_test = len_test_data;
    size_t n = len_training_data;
    Bashint **mini_batches = malloc(sizeof(Bashint) * epoch * n);
    size_t k;
    size_t l;
    for (int j = 0; j < epoch; ++j)
    {
        training_data = suffleBashint(training_data,\
            len_training_data, net.seed);
        //printBashintArray(training_data, len_training_data);
        for (k = 0; k < n; k += mini_bash_size)
        {
            mini_batches[j + k] = cutarrayBashint(training_data,\
                k,k+mini_bash_size);
        }
        for (l = 0; l < n / mini_bash_size; ++l)
        {
            mini_batches[l] = update_mini_bash(training_data,\
                mini_bash_size,eta,&net);
        }
        if(test_data)
        {
            printf("%2d: %f / %zu\n",j,evaluate(test_data,\
                len_test_data,net),n_test);
        }
        else
            printf("Epoch %d complete.\n", j);
    }
    return net;
}

void fprintArrayIntLen(FILE *nr, int *array, int len)
{
    for (int i = 0; i < len; ++i)
    {
        fprintf(nr, "%d ", array[i]);
    }
}

//to save network in a file
void saveNr(Network net, char *fileName)
{
    FILE *nr;
    nr = fopen(fileName, "w+");
    int i, j;
    fprintf(nr, "%d\n", net.lenlayers); //net.lenlayers
    j = 0;
    for (i = 0; i < net.lenlayers; ++i)
    {
        j += net.numLayers[i];
        fprintf(nr, "%d\n", net.numLayers[i]);
    }
    fprintf(nr, "\n%ld\n", net.seed);
    fprintf(nr, "%d\n", net.len);
    for (i = 0; i < net.len; ++i)
    {
        fprintf(nr, "%d\n", net.sizes[i]);
    }
    fprintf(nr, "\n%d\n", j + net.lenbiases);
    for (i = 0; i < net.lenbiases + j; ++i)
    {
        fprintf(nr, "%f\n", net.biases[i]);
    }
    fprintf(nr, "\n%d\n", net.lenweight);
    for (i = 0; i < net.lenweight; ++i)
    {
        fprintf(nr, "%f\n", net.weight[i]);
    }
    fclose(nr);
}

//open a .nr file to get a previouly saved network : WORK IN PROGRESS
Network openNr(char *fileName)
{
    FILE *nr;
    Network net;
    nr = fopen(fileName, "r");
    if (nr == NULL) {
        net.len = -1;
        return net;
    }
    //INITIATING NETWORK !
    int    *numLayers;  //number of neurons by layers
    int     lenlayers;  //len of numLayers
    time_t  seed;       //seed to initiate random
    int    *sizes;      //list of bite of the letter
    int     len;        //len of size
    double *biases;     //list of biases for neurons
    int     lenbiases;  //nb neurons
    double *weight;     //list of weights for neurons
    int     lenweight;  //nb neurons //useless len biases == lenweights

    int i, j=0, res = 0;
    res = fscanf(nr, "%d\n", &lenlayers);
    numLayers = malloc(sizeof(int) * lenlayers);
    for(i = 0; i < lenlayers; ++i)
    {
        res = fscanf(nr, "%d\n", &numLayers[i]);
        j += numLayers[i];
    }
    res = fscanf(nr, "\n%ld\n", &seed);
    res = fscanf(nr, "%d\n", &len);
    sizes = malloc(sizeof(int) * len);
    for (i = 0; i < len; ++i)
    {
        res = fscanf(nr, "%d\n", &sizes[i]);
    }
    res = fscanf(nr, "\n%d\n", &lenbiases);
    lenbiases -= j;
    biases = malloc(sizeof(double) * lenbiases);
    for (i = 0; i < lenbiases; ++i)
    {
        res = fscanf(nr, "%lf\n", &biases[i]);
        //printf("%d : %d\n", lenbiases, i);
    }
    res = fscanf(nr, "\n%d\n", &lenweight);
    weight = malloc(sizeof(double) * lenweight);
    for (i = 0; i < lenweight; ++i)
    {
        res = fscanf(nr, "%lf\n", &weight[i]);
    }
    fclose(nr);
    res           += 1;
    net.numLayers = numLayers;
    net.lenlayers = lenlayers;
    net.seed      = seed;
    net.sizes     = sizes;
    net.len       = len;
    net.biases    = biases;
    net.lenbiases = lenbiases;
    net.weight    = weight;
    net.lenweight = lenweight;
    return net;
}

Bashint unsignedmatToBashint(UnsignedMatrix *matrix){
  Bashint basht;
  basht.input      = malloc(sizeof(double) * 900);
  printf("lines : %zu ; cols %zu\n", matrix->lines, matrix->cols);
  for(size_t i = 0; i < 900; ++i){
    basht.input[i] = (double)matrix->data[i];
  }
  basht.res = -1;
  free_unsigned_matrix(matrix);
  return basht;
}

UnsignedMatrix **from_img_to_letters(char *filepath,size_t *len){
  size_t lines = bmpWidth(filepath);
  size_t cols = bmpHeight(filepath);
  SDL_Surface *surf;
  init_sdl();
  PixelMatrix *image = new_pixel_matrix(lines, cols);
  //printf("Display image : %s\n", filepath);
  surf = load_image(filepath);
  save_image(surf, image);
  UnsignedMatrix *mat = new_unsigned_matrix(lines, cols);
  binarize(image, mat);
  free_pixel_matrix(image);

  UnsignedMatrix *matrix = copy_mat(mat);

  MatBinTree *mbt = new_matbintree(matrix);
  xycut_test(mbt,1,1,10);
  UnsignedMatrix **mats = get_letters(mbt,len);

  free_matbintree(mbt);
  SDL_FreeSurface(surf);
  free_unsigned_matrix(mat);
  return mats;
}

int *setNetwork(int type, int nbPixels)
{
    int *res = malloc(sizeof(int) * 3);
    if (type == 1) //xor -> set len to 3
    {
        *res       = 2 ; //input neurons
        *(res + 1) = 3 ;
        *(res + 2) = 1 ; //output neurons
    }
    if (type == 4)//picture recognition [0-9]
    {
        *res       = nbPixels;
        *(res + 1) = 100;//fixme
        *(res + 2) = 10;
    }
    if (type == 3)//picture recognition [0-9a-zA-Z]
    {
        *res       = nbPixels;
        *(res + 1) = 100;//fixme
        *(res + 2) = 62;
    }
    if (type == 2)//picture recognition UTF08
    {
        *res       = nbPixels;
        *(res + 1) = 100; //fixme
        *(res + 2) = 223;
    }
    return res;
}

char *concatenate(char* a,char* b){
  size_t la = strlen(a);
  size_t lb = strlen(b);
  char* res = malloc((la + lb + 1) * sizeof(char));
  strcpy(res,a);
  strcat(res,b);
  return res;
}

char *get_string(MatBinTree *mbt, Network net){
    if (mbt) {
      if (!mbt->left && !mbt->right) {
        UnsignedMatrix *mat = expand_mat(mbt->key,30,30);
        //mbt->txt          = "b";
        Bashint input       = unsignedmatToBashint(mat);
        mbt->txt            = useNetwork(net, input);
        //free_unsigned_matrix(mat);
        return mbt->txt;
      }
      else{
        if (mbt->ver) {
          char* temp = concatenate(get_string(mbt->left, net)," ");
          mbt->txt   = concatenate(temp,get_string(mbt->right, net));
          return mbt->txt;
        }
        if (mbt->hor) {
          char *temp = concatenate(get_string(mbt->left, net),"\n");
          mbt->txt   = concatenate(temp,get_string(mbt->right, net));
          return mbt->txt;
        }
        mbt->txt = concatenate(get_string(mbt->left, net),get_string(mbt->right, net));
        return mbt->txt;

        //free(temp);
      }

    }
    return "";

}
char* appendChar(char *a, char *b){
    size_t la , lb ;
    la        = strlen(a);
    lb        = strlen(b);
    
    printf("la : %zu,lb : %zu\n",la,lb );
    char* res = malloc((la + lb + 1) * sizeof(char));
    
    strcpy(res,a);
    printf("%s\n", a);
    strcat(res ,b);
    
    return res;

    //printf("%s\n", res);
}

char *castIntToCharStar(int arg){
    char *res = malloc(sizeof(char) * 2);
    res[0] = arg + 33;
    res[1] = '\0';
    return res;
}

char *useNetwork(Network net, Bashint input){
    int min_len =
        (net.lenbiases > net.lenweight ? net.lenweight : net.lenbiases);
    return castIntToCharStar(argmax(feedforward(net, input.input), min_len));
}

Network trainNet(Network net){
    char *res  = malloc(sizeof(char) * 300);
    FILE *file = fopen("NeuralNetWork/trainingData/test.txt", "r");
    char tmp = '0';
    size_t i = 0;
    int rep = 0;
    while(tmp != '\n'){
        rep += fscanf(file, "%c", &tmp);
        res[i] = tmp;
        i++;
    }
    fclose(file);
    res[i + 1] = '\0';
    //open test.bmp files located on : /NeuralNetWork/trainingData/test.bmp
    //open resolution on /NeuralNetWork/trainingData/res.txt
    size_t len1 = strlen(res), len2 = 0;
    char *filePath        = "NeuralNetWork/trainingData/test.bmp";
    UnsignedMatrix **mats = from_img_to_letters(filePath,&len2);
    Bashint *testBash     = malloc(sizeof(Bashint) * len1);
    for(i = 0; i < len1; ++i){
      testBash[i] = unsignedmatToBashint(mats[i]);
      printf("coucou %zu : %zu\n", i, len1); 
    }
    suffleBashint(testBash, len1, net.seed);
    //put them on a Bashint* and then shuffle this list
    //make them go thru th neural network and recover data to improve it
    net.biases[0] += 1;
    return net;
}

Network createNetwork(){
    int len = 3;// set number of layers
    int nbPixels = 900; // set number of input neurons
    int type = 2; //see setNetwork funct to see why
    Network net = makeNetWork(len, setNetwork(type, nbPixels)); //create network
    return net;
}

Network getNetwork(char *filePath){
    Network net = openNr(filePath);
    if (net.len == -1) {//no previously saved network fail :/
        net = createNetwork();
    }
    //net = trainNet(net);
    return net;
}
/*
int mainNetwork(char *filePath, int argc, Bashint *input,
    size_t lenInpout, int noMessinfWithNetworks){
    if(noMessinfWithNetworks){//Not user Friendly :/
        filePath = appendChar(filePath, "01");
        return 0;
    }
    Network net = openNr(filePath);
    if (net.len == -1) //no previously saved network fail :/
    {
      int len = 3;// set number of layers
      int nbPixels = 900; // set number of input neurons
      int type = 2; //see setNetwork funct to see why


      net = makeNetWork(len, setNetwork(type, nbPixels)); //create network
      printf("Created network :\n");
      //printNetwork(net);
      //improving it :
      net = trainNet(net);
      //storing it:
      printf("Improved Network :\n");
      //printNetwork(net);
      saveNr(net, filePath);
      printf("Network saved.\n");
      freeNetwork(net);
      return 0;
    }
    printf("This network was already stored :\n");
    printNetwork(net);
    int rep = 0;
    printf("Do you want to improve it ? \n");
    if((argc = scanf("%d", &rep)) == 0){
      errx(1, "Not an valid input");
    }
    else{
      if(rep){ //want to improve it cf l660
        net = trainNet(net);
        saveNr(net, filePath);
        printf("Network saved.\n");
        freeNetwork(net);
      }
      else{ // nop use it !
        char *res = "";
        for (size_t i = 0; i < lenInpout; ++i)
        {
            //appendChar(res, useNetwork(net, input[i]));
        }
        //USE RES!!!

        return 0;
      }
    }
    //freeNetwork(net);
    return 0;
}
*/
