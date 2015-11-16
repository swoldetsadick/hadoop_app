#include <stdio.h>
#include "com_example_jni_CudaWrapper.h"

JNIEXPORT jint JNICALL Java_com_example_jni_CudaWrapper_CUDAProxy_1matrixMul(JNIEnv *env, jobject obj, jfloatArray aArray, jfloatArray bArray, jfloatArray cArray, jint n)
{
	int i = 0, j = 0;
	jsize N;
	//printf("C: fetching arrays from Java\n");
	jfloat *a = (*env)->GetFloatArrayElements(env, aArray, 0);
	jfloat *b = (*env)->GetFloatArrayElements(env, bArray, 0);
	jfloat *c = (*env)->GetFloatArrayElements(env, cArray, 0);
	//printf("C: Got reference to all a, b, and c\n");
	N = (*env)->GetArrayLength(env, aArray);
	//printf("C: calling CUDA kernel\n");
	printf("C: array size = %d\n", N);
	cuda_matrixAdd(a, b, c, n);

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%1.0f", c[i*n+j]);
		}
	}

	//printf("C: back from CUDA kernel, coping data to Java\n");
	(*env)->ReleaseFloatArrayElements(env, aArray, a, 0);
	(*env)->ReleaseFloatArrayElements(env, bArray, b, 0);
	(*env)->ReleaseFloatArrayElements(env, cArray, c, 0);
	//printf("C: Going back to Java\n");

	return (jint) N; // this might not be the right way to return values to Java
}
