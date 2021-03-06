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
float sigmoid(float z)
{  //explicit content
    return 1.0 / (1.0 + exp(z));
}
float *sigmoidStar(float *z, int len)
{  //explicit content
    float *res = malloc(sizeof(float) * len);
    for (int i = 0; i < len; ++i)
    {
        res[i] = sigmoid(z[i]);
    }
    return res;
}
float sigmoidPrime(float z)
{  //explicit content
    return sigmoid(z) * (1 - sigmoid(z));
}

float dotfloat(float coeff, float *a, int len)
{  //do a dot mathematical function :3 coucou
    //printf("dot : %f  len = %d", coeff, len);
    float res = 0;
    if (coeff == 0 || len == 0)
        return 0;
    for (int i = 0; i < len; ++i)
    {
        //printf("dotfloat : i = %d len = %d a[%d] = %f :\n", i, len, i, a[i]);
        res += a[i] * coeff;
    }
    //printf("res = %f\n", res);
    return res;
}
int lenfloat(float *a){
    int res = 0;
    while(a[res]){
        res++;
    }
    return res;
}
int lenfloat2(float **a){
    int res = 0;
    while (a[res]){
        res ++;
    }
    return res;
}
float **dot2star(float **a, float **b){
    int lena        = lenfloat(a[0]);
    int lena2       = lenfloat2(a);
    float **res = malloc(sizeof(float *) * lena2);
    for(int i = 0; i < lena2; ++i){
        res[i] = malloc(sizeof(float) * lena);
        for(int j = 0; j < lena; ++j){
            res[i][j] = 0;
            for(int k = 0; k < lena2; ++k){
                res[i][j] += a[i][k] + b[k][j];
            }
        }
    }
    return res;
}

float *dot_weights(Network net,int a, float* b){
    if (a)
    {
        float *c = malloc(net.sizes[2] * sizeof(float));
        for (int i = 0; i < net.sizes[2]; ++i)
        {
            c[i] = 0;
            for (int j = 0; j < net.sizes[1]; ++j)
            {
                c[i] += accessWeights(net,a,i,j) * b[j];
            }
            c[i] += accessBiases(net,a,i);
        }
        return c;
    }
    else{
        float *c = malloc(net.sizes[1] * 1 * sizeof(float));
        for (int i = 0; i < net.sizes[1]; ++i)
        {
            c[i] = 0;
            for (int j = 0; j < 900; ++j)
            {
                c[i] += accessWeights(net,a,i,j) * b[j];
            }
            c[i] += accessBiases(net,a,i);
        }
        return c;

    }
}

float *cost_derivate(float* a,float val,int len){
    float *b = malloc(len * sizeof(float))

    for (int i = 0; i < len; ++i)
    {
        b[i] = a[i] - val;
    }
    return b;
}

float *append(float *a, float *b, int lenA, int lenB)
{  //To append two list a and b.
    float *res = malloc(sizeof(a) * lenA + sizeof(b) * lenB);
    res = a;
    for (int i = lenA; i < lenB; ++i)
    {
        res[i] = *b;
    }
    return res;
}

//########################access################################

float accessBiases(Network net, int a, int b){
    return net.biases[net.sizes[2] * a + b];
}

float accessWeights(Network net, int a, int b, int c){
    if(a == 0){
        return net.weight[b * net.sizes[0] + c];
    }
    else{
        return net.weight[net.sizes[0] * net.sizes[1] + b * net.sizes[2] + c];
    }
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
    printf("#~~~~~~~~~~~~ Test ~~~~~~~~~~~#\n");
    printf("|res : %d                     |\n|Input :                       |\n|", (int)b.res);
    int i = 0;
    for (i = 0; i < 900; ++i)
    {
        if(b.input[i]){
            printf("#");
        }
        else
        {
            printf(" ");
        }
        if(i%30 == 29){
            printf("|\n|");
        }
    }
    printf("                              |\
          \n#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#\n");
}
void printBashintArray(Bashint *a, int len)
{
    for (int i = 0; i < len; ++i)
    {
        printf(" Bashint n° %d\n", i);
        printBashint(a[i]);
    }
}
void printfloatarray(float *array)
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
    net.lenbiases = sizes[1] + sizes[2];
    //len
    net.len   = len;
    //sizes
    net.sizes = sizes;
    //seed
    net.seed  = time(NULL);
    srand(net.seed);
    //*biases
    net.biases = malloc(sizeof(float) * net.lenbiases);
    for (int i = 0; i < net.lenbiases; ++i)
    {
        net.biases[i] = ((float)rand()/(float)RAND_MAX);
    }
    //lenweight
    //len first  = [0] * [1]
    //len second = [1] * [2]
    net.lenweight = sizes[0] * sizes[1] + sizes[1] * sizes[2];
    //*weight
    net.weight = malloc(sizeof(float) * net.lenweight);
    for (int j = 0; j < net.lenweight; ++j)
    {
        net.weight[j] = ((float)rand()/(float)RAND_MAX);
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
void freefloat2star(float **a, int len)
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
        float *tmp = malloc(sizeof(float) * 2);
        *tmp = rand()%2;
        *(tmp + 1) = rand()%2;
        b.res = xor(*tmp, *(tmp + 1));
        b.input = tmp;
        res[i] = b;
    }
    //printBashintArray(res, len);
    return res;
}
void suffleBashint(Bashint *bash, int len, time_t seed)
{ //to shuffle all elts in the BashintArray
    srand(seed);
    int pos;
    Bashint tmp;
    for (int i = 0; i < len - 1; ++i)
    {
        pos = rand() % (len - i - 1);
        //printf("len = %d, i = %d, pos = %d\n", len , i, pos);
        tmp = bash[pos];
        bash[pos] = bash[len - i - 1];
        bash[len - i - 1] = tmp;
    }
}
float *cutarray(float *array, int posmin, int posmax)
{
    //printf("cut : %d, %d\n", posmin, posmax);
    //printfloatarray(array);
    int len = posmax - posmin;
    float *res = malloc(sizeof(float) * len);
    for (int i = 0; i < len; ++i)
    {
        res[i] = array[i + posmin];
    }
    return res;
}
void backprop(Network *network, float **deltas,float *x, float y) //may be done .....
{
    Network net = *network;
    //init:
    //printf("net.lenbiases = %d\n", net.lenbiases);
    float *nabla_b = malloc(sizeof(float) * net.lenbiases);
    //printf("passed\n");
    int i;
    //printf("backprop : 2\n");
    for(i = 0; i < net.lenbiases; ++i)
    {
        nabla_b[i] = 0;
    }
    //printf("backprop : 3\n");
    float *nabla_w = malloc(sizeof(float) * net.lenweight);
    for(i = 0; i <net.lenweight; ++i)
    {
        nabla_w[i] = 0;
    }
    //printf("backprop : 4\n");
    //feedforward
    float *activation = malloc(sizeof(float) * 900);
    for(i = 0; i < 900; ++i){
        activation[i] = x[i];
    }

    int min_len =
        (net.lenbiases > net.lenweight ? net.lenweight : net.lenbiases);
    //printf("min_len = %d\n", min_len);
    float **activations = malloc(sizeof(float *) * 3);
    activations[0]         = activation;
    float **zs          = malloc(sizeof(float *) * 2);
    int thisLayerWieght  = 0;
    int nbneuronsleft    = net.numLayers[0];
    int posmininweight   = 0;

    zs[0] = dot_weights(net,0,activation);
    activations[1] = sigmoidStar(zs[0],net.sizes[1]);
    zs[1] = dot_weights(net,1,activations[1]);
    activations[2] = sigmoidStar(zs[1],net.sizes[2]);

    //printf("backprop : 6\n");
    float* delta = cost_derivate(activation[2],y,net.sizes[2]);
    for (int i = 0; i < net.sizes[2]; ++i)
    {
        delta[i] *= sigmoidPrime(zs[1][i]);
    }

    for (int i = net.sizes[1]; i < net.lenbiases; ++i)
    {
        nabla_b[i] = delta[i];
    }

    float *temp = dot_weights(delta,)
    //printf("backprop : 7\n");
    for (int l = 2; l < net.lenlayers; ++l)
    {
        z                    = zs[min_len - l];
        sp                   = sigmoidPrime(z);
        //no transposition : useless....
        delta = dotfloat(delta, net.weight, net.lenweight - l - 1) * sp;
        nabla_b[min_len - l] = delta;
        nabla_w[min_len - l] = dotfloat(delta, activations[l],
            min_len - l - 1) * sp;

        //printf("backprop : 7.%d\n", l);
    }
    //printf("backprop : 8\n");
    //building result
    deltas[0]   = nabla_b;
    deltas[1]   = nabla_w;
    //free
    *network = net;
    free(activations);
    free(zs);
    //free(nabla_b);
    //free(nabla_w);
    //I'm freeeee, from my worries
    //return res;
}
void update_mini_bash(Bashint *mini_bash, size_t len_mini_bash,
    float eta, Network *network, Bashint *res) //done
{
    //printf("update_mini_bash : 0\n");
    Network net = *network;
    //initialization:
    float *nabla_b = malloc(sizeof(float) * net.lenbiases);
    int i;
    //printf("update_mini_bash : 1\n");
    for (i = 0; i < net.lenbiases; ++i)
    {
        nabla_b[i] = 0;
        //printf("update_mini_bash : 2 : i = %d\n", i);
    }
    float *nabla_w = malloc(sizeof(float) * net.lenweight);
    for (i = 0; i < net.lenweight; ++i)
    {
        nabla_w[i] = 0;
        //printf("update_mini_bash : 3 : i = %d\n", i);
    }
    //loop
    //printf("update_mini_bash : 4\n");
    Bashint b;
    float *x;
    float y;
    float **deltas = malloc(sizeof(float *) * 2);
    int j;
    size_t w;
    for(size_t j = 0; j < len_mini_bash; ++j){
        res[j] = mini_bash[j];
    }
    //printf("update_mini_bash : 5\n");
    for (w = 0; w < len_mini_bash; ++w)
    {
        b = res[w];
        x = b.input;
        y = b.res;
        //printf("update_mini_bash5.2 w = %zu\n", w);
        //printBashint(b);
        //printf("update_mini_bash : 5.5\n");
        //deltas =
        backprop(network,deltas, x, y);
        //deltas[0] == delta_nabla_b and deltas[1] == delta_nabla_w
        //printf("update_mini_bash : 6 w = %zu\n", w);
        for(j = 0; j < net.lenbiases; ++j)
        {
            nabla_b[j] += deltas[0][j];
        }
        //printf("update_mini_bash : 6.5\n");
        for(j = 0; j < net.lenweight; ++j)
        {
            //printf("j = %d %f\n", j, deltas[1][j]);
            nabla_w[j] += deltas[1][j];
        }
    }
    //printf("update_mini_bash : 7\n");
    int k;
    for (k = 0; k < net.lenweight; ++k)
    {
        net.weight[k] = net.weight[k] - (eta / len_mini_bash) * nabla_w[k];
    }
    //printf("update_mini_bash : 8\n");
    for(k = 0; k < net.lenbiases; ++k)
    {
        net.biases[k] = net.biases[k] - (eta / len_mini_bash) * nabla_b[k];
    }
    //printf("update_mini_bash : 9(the end)\n");
    *network = net;
    //free
    //free(nabla_b);
    //free(nabla_w);
}
void feedforward(Network net, float *x, float *res)
{
    int min_len =
        (net.lenbiases > net.lenweight ? net.lenweight : net.lenbiases);
    printf("%d\n", net.lenweight);
    for (int i = 0; i < min_len; ++i)
    {
        float y = dotfloat(net.weight[i], x, min_len);
        res[i] = sigmoid(y + net.biases[i]);
        //printf("feed : y = %f b[%d] = %f res = %f\n", y, i, net.biases[i], res[i]);
    }
}
int argmax(float *array, int len)
{
    int res = 0;
    for (int i = 1; i < len; ++i)
    {
        if(array[i] > array[res])
            res = i;
    }
    return res;
}
void printList(float *input, int len){
    int i = 0;
    while(i < len){
        printf("%d : %f ", i, input[i]);
        i++;
        if(i % 5 == 0){
            printf("\n");
        }
    }
}
float evaluate(Bashint *test_data, int len_test_data, Network net)
{
    float res = 0;
    float **test_result = malloc(sizeof(float*) * len_test_data);
    int min_len =
        (net.lenbiases > net.lenweight ? net.lenweight : net.lenbiases);
    //building test_result
    //printBashintArray(test_data, len_test_data);
    float *tmpFloatList = malloc(sizeof(float) * min_len);
    //float *tmpFloatList2 = malloc(sizeof(float) * min_len);
    for (int i = 0; i < len_test_data; ++i)
    {
        //printf("i : %d len_test_data = %d\n",i, len_test_data);
        test_result[i] = malloc(sizeof(float) * 2);
        //printBashint(test_data[i]);
        feedforward(net,test_data[i].input, tmpFloatList);
        //tmpFloatList2 = cutarray(tmpFloatList, 100, 126);
        //printList(tmpFloatList2, 26);
        test_result[i][0] = (float)argmax(tmpFloatList + 100, 26);
        test_result[i][1] = test_data[i].res;
        printf("Result : %f == %f\n", test_result[i][0], test_result[i][1]);
    }
    //free(tmpFloatList);
    //compute test_result
    //printBashintArray(test_data, len_test_data);
    for (int i = 0; i < len_test_data; ++i)
    {
        //printf("evaluate : i = %d : x = %f et y = %f\n", i, test_result[i][0], test_result[i][1]);
        if (test_result[i][0] == test_result[i][1])
            res += 1;
    }
    freefloat2star(test_result, len_test_data);
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
    int epoch, int mini_bash_size, float eta, Bashint *test_data,\
    int len_test_data)//V2
{
    size_t n_test = mini_bash_size;
    size_t n = len_training_data;
    Bashint **mini_batches = malloc(sizeof(Bashint) * epoch * n);
    size_t k;
    size_t l;
    for (int j = 0; j < epoch; ++j)
    {
        //printBashintArray(training_data, len_training_data);
        printf("SGD : 3\n");
        suffleBashint(training_data, len_training_data, net.seed);
        printf("SGD : 4\n");
        //printBashintArray(training_data, len_training_data);
        for (k = 0; k < n; k += mini_bash_size)
        {
            mini_batches[j + k] = cutarrayBashint(training_data,\
                k,k+mini_bash_size);
        }
        printf("SGD : 5\n");
        for (l = 0; l < n / mini_bash_size; ++l)
        {
            update_mini_bash(training_data, mini_bash_size,eta,&net,\
                mini_batches[l]);
        }
        printf("SGD : 6\n");
        if(test_data)
        {
            size_t x = 0;
            while(mini_batches[x]){
                x++;
            }
            printf("%2d: %f / %zu\n",j,evaluate(test_data,\
                len_test_data,net),n_test);
        }
        else{
            printf("Epoch %d complete.\n", j);
        }
        printf("SGD : 7(the end)\n");
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
    nr = fopen(fileName, "r");
    Network net;
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
    float *biases;     //list of biases for neurons
    int     lenbiases;  //nb neurons
    float *weight;     //list of weights for neurons
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
    biases = malloc(sizeof(float) * lenbiases);
    for (i = 0; i < lenbiases; ++i)
    {
        res = fscanf(nr, "%f\n", &biases[i]);
        //printf("%d : %d\n", lenbiases, i);
    }
    res = fscanf(nr, "\n%d\n", &lenweight);
    weight = malloc(sizeof(float) * lenweight);
    for (i = 0; i < lenweight; ++i)
    {
        res = fscanf(nr, "%f\n", &weight[i]);
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

Bashint *unsignedmatToBashint(UnsignedMatrix *matrix){
  Bashint *basht = malloc(sizeof(Bashint));
  basht->input      = malloc(sizeof(float) * 1000);
  for(size_t i = 0; i < 900; ++i){
    basht->input[i] = (float)matrix->data[i];
  }
  basht->res = -1;
  free_unsigned_matrix(matrix);
  return basht;
}

UnsignedMatrix **from_img_to_letters(char *filepath, size_t *len){
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
        //*res       = nbPixels;
        //*(res + 1) = 100; //fixme
        //*(res + 2) = 223;
        res[0] = nbPixels;
        res[1] = 100;
        res[2] = 26;
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

char* add_spaces(char* a,size_t n){
  size_t len = strlen(a);
  char *new = malloc((len + n) * sizeof(char));
  strcpy(new,a);
  if (n == 0) {
    return new;
  }
  for (size_t i = len - 1; i < len + n; i++) {
    new[i] = ' ';
  }
  new[len + n - 1] = '\0';
  return new;
}

char *get_string(MatBinTree *mbt, Network net){
    if (mbt) {
      if (!mbt->left && !mbt->right) {
        UnsignedMatrix *mat = expand_mat(mbt->key,30,30);
        mbt->txt          = "b";
        //Bashint input       = unsignedmatToBashint(mat);
        //mbt->txt            = useNetwork(net, input);
        free_unsigned_matrix(mat);
        return mbt->txt;
      }
      else{
        if (mbt->ver) {
          char* temp = add_spaces(get_string(mbt->left, net),mbt->ver / 10);
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
    float *tmpFloatList = malloc(sizeof(float) * min_len);
    feedforward(net, input.input, tmpFloatList);
    int res = argmax(tmpFloatList, min_len);
    char *resFinal = castIntToCharStar(res);
    return resFinal;
}
/**
 * Easy training of the neural Network !
 * @param  Net network to improve
 * @return     The improved network ;)
 */
Network trainNet(Network net){
    char *res  = malloc(sizeof(char) * 500);
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
    size_t len2 = 0;
    char *filePath        = "NeuralNetWork/trainingData/test.bmp";
    UnsignedMatrix **mats = from_img_to_letters(filePath,&len2);
    Bashint *testBash     = malloc(sizeof(Bashint) * len2 * 2);
    for(i = 0; i < len2; ++i){
        testBash[i] = *unsignedmatToBashint(mats[i]);
        testBash[i].res = i;
    }
    //printBashintArray(testBash, len2);
    suffleBashint(testBash, len2, net.seed);
    //put them on a Bashint* and then shuffle this list
    //make them go thru th neural network and recover data to improve it
    int epoch = 1;
    float eta = 3.0;

    //Bashint *test_data = malloc(sizeof(Bashint) * len2/2);
    //for(size_t j = 0; j < len2 / 2; ++j){
    //    test_data[j] = testBash[i];
    //}

    net = SGD(net, testBash, len2, epoch, 16, eta, testBash, len2/2);
    return net;
}

Network createNetwork(){
    int len = 3;// set number of layers
    int nbPixels = 900; // set number of input neurons
    int type = 2; //see setNetwork funct to see why
    int *typeOfNet = setNetwork(type, nbPixels);
    Network net = makeNetWork(len, typeOfNet); //create network
    return net;
}

Network getNetwork(char *filePath){
    Network net = openNr(filePath);
    net.len = -1;
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
