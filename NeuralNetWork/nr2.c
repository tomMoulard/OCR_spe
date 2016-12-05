  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270
271
272
273
274
275
276
277
278
279
280
281
282
283
284
285
286
287
288
289
290
291
292
293
294
295
296
297
298
299
300
301
302
303
304
305
306
307
308
309
310
311
312
313
314
315
316
317
318
319
320
321
322
323
324
325
326
327
328
329
330
331
332
333
334
335
336
337
338
339
340
341
342
343
344
345
346
347
348
349
350
351
352
353
354
355
356
357
358
359
360
361
362
363
364
365
366
367
368
369
370
371
372
373
374
375
376
377
378
379
380
381
382
383
384
385
386
387
388
389
390
391
392
393
394
395
396
397
398
399
400
401
402
403
404
405
406
407
408
409
410
411
412
413
414
415
416
417
418
419
420
421
422
423
424
425
426
427
428
429
430
431
432
433
434
435
436
437
438
439
440
441
442
443
444
445
446
447
448
449
450
451
452
453
454
455
456
457
458
459
460
461
462
463
464
465
466
467
468
469
470
471
472
473
474
475
476
477
478
479
480
481
482
483
484
485
486
487
488
489
490
491
492
493
494
495
496
497
498
499
500
501
//the second
#include "nr2.h"

double sigmoid(double input){
	return 1.0 / (1.0 + exp(- input));
}
double sigmoidPrime(double input){
	double tmp = sigmoid(input);
	return tmp *( 1.0 - tmp);
}
double rando(){
	return (double)rand()/((double)RAND_MAX+1);
}
void shuffle(double *input, int len){
	double tmp;
	int pos = 0;
	for(int i = 0; i < len - 1; i++){
		pos                = rand() % (len - i - 1);
		tmp                = input[pos];
		input[pos]         = input[len - i - 1];
		input[len - i - 1] = tmp;
	}
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

void printNr(Network *net){
	for(int i = 0; i < net->NumInput  + 1; i++){
		for(int j = 0; j < net->NumHidden;j++){
			printf("net->deltaWeightLH[%d][%d] = %f\n", i, j, net->deltaWeightLH[i][j]);
			printf("net->WeightLH[%d][%d]      = %f\n", i, j, net->WeightLH[i][j]);
		}
	}
	for(int i = 0; i < net->NumOutput  + 1; i++){
		for(int j = 0; j < net->NumHidden;j++){
			printf("net->deltaWeightHO[%d][%d] = %f\n", j, i, net->deltaWeightHO[j][i]);
			printf("net->WeightHO[%d][%d]      = %f\n", j, i, net->WeightHO[j][i]);
		}
	}
	printf("Error : %f\n", net->Error);
	printf("Numpattern : %d\n", net->Numpattern);
	printf("NumHidden : %d\n", net->NumHidden);
	printf("NumInput : %d\n", net->NumInput);
	printf("NumOutput : %d\n", net->NumOutput);
	printf("\n");
}

Network *OpenNrFromFile(char *filePath){
	Network *net = malloc(sizeof(Network));
	//net->NumInput = -1;
	//return net;
	FILE *nr = fopen(filePath, "r");
	if(nr == NULL){
		net->NumInput = -1;
		return net;
	}
	fscanf(nr, "%f\n", &net->Error);
	fscanf(nr, "%d\n", &net->Numpattern);
	fscanf(nr, "%d\n", &net->NumHidden);
	fscanf(nr, "%d\n", &net->NumInput);
	fscanf(nr, "%d\n", &net->NumOutput);
	net->deltaWeightLH = malloc(sizeof(double *) * (net->NumInput + 1));
	net->WeightLH      = malloc(sizeof(double *) * (net->NumInput + 1));
	for(int i = 0; i < net->NumInput  + 1; i++){
		net->deltaWeightLH[i] = malloc(sizeof(double) * net->NumHidden);
		net->WeightLH[i]      = malloc(sizeof(double) * net->NumHidden);
		for(int j = 0; j < net->NumHidden;j++){
			fscanf(nr,"%lf\n", &net->deltaWeightLH[i][j]);
			fscanf(nr,"%lf\n",  &net->WeightLH[i][j]);
		}
	}
	net->deltaWeightHO = malloc(sizeof(double *) * (net->NumHidden + 1));
	net->WeightHO      = malloc(sizeof(double *) * (net->NumHidden + 1));
	for(int k = 0; k < net->NumHidden + 1; k++){
		net->deltaWeightHO[k] = malloc(sizeof(double) * net->NumOutput);
		net->WeightHO[k]      = malloc(sizeof(double) * net->NumOutput);
	}
	for(int i = 0; i < net->NumOutput  + 1; i++){
		for(int j = 0; j < net->NumHidden;j++){
			fscanf(nr,"%lf\n", &net->deltaWeightHO[j][i]);
			fscanf(nr,"%lf\n", &net->WeightHO[j][i]);
		}
	}
	fclose(nr);
	return net;
}


void freeNetwork(Network *net){
	for(int i = 0; i < net->NumInput  + 1; i++){
		free(net->deltaWeightLH[i]);
		free(net->WeightLH[i]);
	}
	for(int k = 0; k < net->NumHidden + 1; k++){
		free(net->deltaWeightHO[k]);
		free(net->WeightHO[k]);
	}
	free(net->WeightLH);
	free(net->deltaWeightLH);
	free(net->WeightHO);
	free(net->deltaWeightHO);
	free(net->SumDow);
	free(net->deltaH);
	free(net->deltaO);
	for(int i = 0; i < net->Numpattern; i++){
		free(net->SumO[i]);
	}
	free(net->SumO);
	free(net);
}

void saveNr(Network *net, char *filePath){
	FILE *nr = fopen(filePath, "w+");
	fprintf(nr, "%f\n", net->Error);
	fprintf(nr, "%d\n", net->Numpattern);
	fprintf(nr, "%d\n", net->NumHidden);
	fprintf(nr, "%d\n", net->NumInput);
	fprintf(nr, "%d\n", net->NumOutput);

	for(int i = 0; i < net->NumInput  + 1; i++){
		for(int j = 0; j < net->NumHidden;j++){
			fprintf(nr,"%lf\n", net->deltaWeightLH[i][j]);
			fprintf(nr,"%lf\n", net->WeightLH[i][j]);
		}
	}
	for(int i = 0; i < net->NumOutput  + 1; i++){
		for(int j = 0; j < net->NumHidden;j++){
			fprintf(nr,"%f\n", net->deltaWeightHO[j][i]);
			fprintf(nr,"%f\n", net->WeightHO[j][i]);
		}
	}
	fclose(nr);
	freeNetwork(net);
}

Network *initNet(){
    srand(time(NULL));
	Network *net   = malloc(sizeof(Network));
	net->Error     = 0;
	net->NumInput  = 900;
	net->NumOutput = 64;
	net->NumHidden = 800;
	
	double smallWeight = 0.5;

	net->deltaWeightLH = malloc(sizeof(double *) * (net->NumInput + 1));
	net->WeightLH      = malloc(sizeof(double *) * (net->NumInput + 1));
	for(int i = 0; i < net->NumInput  + 1; i++){
		net->deltaWeightLH[i] = malloc(sizeof(double) * net->NumHidden);
		net->WeightLH[i]      = malloc(sizeof(double) * net->NumHidden);
		for(int j = 0; j < net->NumHidden;j++){
			net->deltaWeightLH[i][j] = 0.0;
			net->WeightLH[i][j] = 2.0 * (rando() - 0.5) * smallWeight;
		}
	}
	net->deltaWeightHO = malloc(sizeof(double *) * (net->NumHidden + 1));
	net->WeightHO      = malloc(sizeof(double *) * (net->NumHidden + 1));
	for(int k = 0; k < net->NumHidden + 1; k++){
		net->deltaWeightHO[k] = malloc(sizeof(double) * net->NumOutput);
		net->WeightHO[k]      = malloc(sizeof(double) * net->NumOutput);
	}
	for (int k = 0; k < net->NumOutput; k++)
	{
		for(int j = 0; j < net->NumHidden + 1; j++){
				net->deltaWeightHO[j][k] = 0.0;
				net->WeightHO[j][k] = 2.0 * (rando() - 0.5) * smallWeight;
			}
	}

	net->SumO = malloc(sizeof(double *) * net->NumOutput);
	for(int l = 0; l < net->NumOutput; l++){

	}
	net->SumDow = malloc(sizeof(double) * net->NumHidden);
	net->deltaH = malloc(sizeof(double) * net->NumHidden);
	net->deltaO = malloc(sizeof(double) * net->NumOutput);

	return net;
}
Network *OpenNr(char *filePath){
	Network *net = OpenNrFromFile(filePath);
	//net->NumInput = -1;
	if (net->NumInput == -1){
		net = initNet();
	}
	return net;
}
void printList(double *l, int len){
	for(int i = 0 ; i < len ; ++i){
		printf("%f ", l[i]);
	}
	printf("\n");
}
void trainNetwork(Network *net, size_t _epoch, double eta,\
	double alpha, double **input, double **target, int evalutate){
	net->ranpat = malloc(sizeof(double) * net->Numpattern);
	net->SumH          = malloc(sizeof(double *) * net->Numpattern);
	net->SumO          = malloc(sizeof(double *) * net->Numpattern);
	net->Hidden        = malloc(sizeof(double *) * net->Numpattern);
	net->Output        = malloc(sizeof(double *) * net->Numpattern);
	for(int i = 0; i < net->Numpattern; i++){
		net->Output[i] = malloc(sizeof(double) * net->NumOutput);
		net->SumO[i]   = malloc(sizeof(double) * net->NumOutput);
		net->SumH[i]   = malloc(sizeof(double) * net->NumHidden);
		net->Hidden[i] = malloc(sizeof(double) * net->NumHidden);
	}
	for(size_t epoch = 0; epoch < _epoch; epoch++){
		for(int p = 0; p < net->Numpattern; p++){
			net->ranpat[p] = p;
		}
		//printf("before shuffle :\n");
		//printList(net->ranpat, net->Numpattern);
		shuffle(net->ranpat, net->Numpattern);
		//printf("after :\n");
		//printList(net->ranpat, net->Numpattern);
		net->Error = 0.0;
		for(int np = 0; np < net->Numpattern; np++){
			int p = net->ranpat[np];
			for(int j = 0; j < net->NumHidden;j++){
				net->SumH[p][j] = net->WeightLH[net->NumHidden][j];
				for(int i = 0; i < net->NumInput; i++){
					net->SumH[p][j] += input[p][i] * net->WeightLH[i][j];
				}
				net->Hidden[p][j] = sigmoid(net->SumH[p][j]);
			}
			for(int k = 0; k < net->NumOutput;k++){
				net->SumO[p][k] = net->WeightHO[net->NumHidden][k];
				for(int l = 0; l < net->NumHidden; l++){
					net->SumO[p][k] += net->Hidden[p][l] * net->WeightHO[l][k];
				}
				net->Output[p][k] = sigmoid(net->SumO[p][k]);
				net->Error        += 0.5 * (target[p][k] - net->Output[p][k]) * (target[p][k] - net->Output[p][k]);/* SSE */
				net->deltaO[k]    = (target[p][k] - net->Output[p][k]) * net->Output[p][k] * (1.0 - net->Output[p][k]);
			}
				if(evalutate){ return;}
			for(int j = 0; j < net->NumHidden;j++){
				net->SumDow[j] = 0.0;
				for(int m = 0; m < net->NumOutput; m++){
					net->SumDow[j] += net->WeightHO[j][m] * net->deltaO[m];
				}
				net->deltaH[j] = net->SumDow[j] * net->Hidden[p][j]\
											    * (1.0 - net->Hidden[p][j]);
			}
			for(int j = 0; j < net->NumHidden;j++){
				net->deltaWeightLH[net->NumHidden][j] = eta * net->deltaH[j] + alpha *\
							 net->deltaWeightLH[net->NumHidden][j];
				net->WeightLH[net->NumHidden][j]      += net->deltaWeightLH[net->NumHidden][j];
				for(int n = 0; n < net->NumInput; n++){
					net->deltaWeightLH[n][j] = eta * input[p][n] *\
							 net->deltaH[j] + alpha * net->deltaWeightLH[n][j];
					net->WeightLH[n][j]      += net->deltaWeightLH[n][j] ;
				}
			}
			for(int k = 0; k < net->NumOutput; k++){
				net->deltaWeightHO[net->NumHidden][k] = eta * net->deltaO[k] + alpha *\
									 net->deltaWeightHO[net->NumHidden][k] ;
				net->WeightHO[net->NumHidden][k]      += net->deltaWeightHO[net->NumHidden][k];
				for(int o = 0; o < net->NumHidden ;o++){
                    net->deltaWeightHO[o][k] = eta * net->Hidden[p][o] *\
                    		 net->deltaO[k] + alpha * net->deltaWeightHO[o][k] ;
                    net->WeightHO[o][k] += net->deltaWeightHO[o][k] ;
				}
			}
		}
		if(epoch % 100 == 99){printf("epoch : %zu -> Error : %f\n", epoch, net->Error);}
		if(net->Error < 0.0005){break;}
	}
	//for(int i = 0; i < net->NumOutput; i++){
		//printf("input :\n");
		//for(int j = 0; j < 900; j++){
		//	//printf("%c ", input[i][j]? '#' : ' ');
		//	if(j % 30 == 29){
		//		//printf("\n");
		//	}
		//}
		//printf("\noutput : ");
		//for(int j = 0; j < net->NumOutput; ++j){
			//printf("%f ", net->Output[i][j]);
		//}
		//printf("\n");
	//}

}

/*
int useNetwork(Network net, double *input){
	int res = 0;

	return res;
}*/
/*
int main()//int argc, char const *argv[])
{
	Network *net = initNet();
	net->Numpattern    = 4;
	double **input  = malloc(sizeof(double *) * net->Numpattern);
	input[0] = malloc(sizeof(double) * 2);
	input[0][0] = 0;
	input[0][1] = 1;
	input[1] = malloc(sizeof(double) * 2);
	input[1][0] = 1;
	input[1][1] = 1;
	input[2] = malloc(sizeof(double) * 2);
	input[2][0] = 1;
	input[2][1] = 0;
	input[3] = malloc(sizeof(double) * 2);
	input[3][0] = 0;
	input[3][1] = 0;
	double **target = malloc(sizeof(double *) * net->Numpattern);
	target[0] = malloc(sizeof(double) * 1);
	target[0][0] = 1;
	target[1] = malloc(sizeof(double) * 1);
	target[1][0] = 0;
	target[2] = malloc(sizeof(double) * 1);
	target[2][0] = 1;
	target[3] = malloc(sizeof(double) * 1);
	target[3][0] = 0;
	trainNetwork(net, 100000, 0.1, 0.9, input, target);
	return 0;
}
*/
void trainNetFinal(Network *net){
	char *res  = malloc(sizeof(char) * 500);
    FILE *file = fopen("NeuralNetWork/trainingData/7.txt", "r");
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
    size_t len2 = 0;
    char *filePath        = "NeuralNetWork/trainingData/7.bmp";
    UnsignedMatrix **mats = from_img_to_letters(filePath,&len2);
    len2 = 64;
    //printf("len2 = %zu\n", len2);
    //printf("%d\n",i );
	net->Numpattern    = (int)i - 1;
	double **input  = malloc(sizeof(double *) * net->Numpattern);
	double **target = malloc(sizeof(double *) * net->Numpattern);
    for(i = 0; i < len2; ++i){
		input[i]  = malloc(sizeof(double) * 900);
		for(int j = 0; j < 900; ++j){
			input[i][j] = (double)mats[i]->data[j];
		}
    }
    for(size_t j = 0 ; j < len2; ++j){
		target[j] = calloc(sizeof(double), len2);
		target[j][j] = 1;

    }
    /*
    for(size_t i = 0; i < len2; i++){
		printf("input : %c\n",res[i]);
		for(int j = 0; j < 900; j++){
			printf("%c ", input[i][j]? '#' : ' ');
			if(j % 30 == 29){
				printf("\n");
			}
		}
	}*/

	trainNetwork(net, 1000, 0.02, 0.9, input, target, 0);
}

int useNr(Network *net, double **input){
	double **target = malloc(sizeof(double *));
	target[0] = calloc(sizeof(double), net->NumOutput);
	net->Numpattern = 1;
	trainNetwork(net, 1, 0.01, 0.9, input, target, 1);
	int res = 0;
	for(int i = 0; i < net->NumOutput; ++i){
		//printf("net->Output[0][i] = %f\n", net->Output[0][i]);	
		if(net->Output[0][res] < net->Output[0][i]){
			res = i;
		}
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
  for (size_t i = len; i < len + n; i++) {
    new[i] = ' ';
  }
  new[len + n - 1] = '\0';
  return new;
}

char *get_string(MatBinTree *mbt, Network *net){
    if (mbt) {
      if (!mbt->left && !mbt->right) {
        UnsignedMatrix *mat = expand_mat(mbt->key,30,30);
        double **input = malloc(sizeof(double *));
        input[0] = malloc(sizeof(double) * 900);
        for(int i = 0; i < 900; ++i){
        	input[0][i] = (double)mat->data[i];
        }
		int res         = useNr(net, input);
		printf("%d ", res);
		mbt->txt        = malloc(sizeof(char) * 2);
		mbt->txt[0] = 35;
		if (res == 63)
		{
			mbt->txt[0] = 46;
		}
		else{
			if (res == 62)
			{
				mbt->txt[0] = 44;
			}
			else{
				if (res >= 0)
				{
					mbt->txt[0] = res + 97;
				}
				if(res >= 26){
					mbt->txt[0] = res + 65 - 26;
				}
				if (res >= 52)
				{
					mbt->txt[0] = res - 4;
				}
			}
		}
		//mbt->txt[0]     = res < 26 ?res + 97 : res + 41;
		mbt->txt[1]     = '\0';
		//Bashint input = unsignedmatToBashint(mat);
		//mbt->txt      = useNetwork(net, input);
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
/*
int main()//int argc, char const *argv[])
{
	Network *net = initNet();
	trainNetFinal(net);
	return 0;
}
*/