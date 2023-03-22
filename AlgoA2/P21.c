#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>
#define MAX_LENGTH 30000
//Collin Struthers 1084915 Assignment 2 feb 12 2023
//this file contains the finding the convex hull for a file where the brute force is used. It also displays the shortest path in the convex hull between two points inputted by the user
//structure for storing data
struct Point
{
    double x;
    double y;
};
//keeps track all final values needed
struct Path
{
    double length;
    int numOfPoints;
    struct Point pathPoints[MAX_LENGTH];
    struct Point shortestpathPoint[MAX_LENGTH];
    int numOfShortPathPoints;
};
double min(double value1, double value2)
{
    if (value1 > value2 || value1 == -1)
    {
        return value2;
    }
    else
    {
        return value1;
    }
}

double calculateDistance(struct Point a, struct Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct Path bruteforce(struct Point Arr[], int size)
{
    struct Path distance;
    distance.numOfPoints = 0;
    distance.length = DBL_MAX;
    int count, i, j, k;
    double a, b, c, checkval;
    count = 0;

    for (i = 0; i < size; i++)
    {

        for (j = i + 1; j < size; j++)
        { //new
            if (Arr[i].x == Arr[j].x && Arr[i].y == Arr[j].y)
            {
                continue;
            }
            int sign = 0;
            bool extremeline = false;
            a = Arr[j].y - Arr[i].y;
            b = Arr[i].x - Arr[j].x;
            c = (Arr[i].x * Arr[j].y) - (Arr[i].y * Arr[j].x);

            for (k = 0; k < size; k++)
            {
                //new
                if ((Arr[k].x == Arr[i].x && Arr[k].y == Arr[i].y) || (Arr[k].x == Arr[j].x && Arr[k].y == Arr[j].y))
                {
                    continue;
                }
                checkval = (a * Arr[k].x) + (b * Arr[k].y) - c;

                if (sign != 0)
                {
                    if (checkval > 0 && sign < 0)
                    {
                        extremeline = false;
                        break;
                    }
                    else if (checkval < 0 && sign > 0)
                    {
                        extremeline = false;
                        break;
                    }
                    else
                    {
                        extremeline = true;
                    }
                }
                else
                {
                    if (checkval > 0)
                    {
                        sign = 1;
                    }
                    else if (checkval < 0)
                    {
                        sign = -1;
                    }
                }
            }

            if (extremeline)
            {
                // distance.pathPoints[count++] = Arr[i];
                bool found = false;
                // printf("%lf %lf\n", Arr[i].x, Arr[j].x);
                for (k = 0; k < count; k++)
                {
                    if (distance.pathPoints[k].x == Arr[i].x && distance.pathPoints[k].y == Arr[i].y)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    distance.pathPoints[count++] = Arr[i];
                }
                found = false;
                for (k = 0; k < count; k++)
                {
                    if (distance.pathPoints[k].x == Arr[j].x && distance.pathPoints[k].y == Arr[j].y)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    distance.pathPoints[count++] = Arr[j];
                }

                distance.numOfPoints = count;
            }
        }
    }

    return distance;
}
//start at point p1
//find the point closet to p1,
struct Path shortestpath(struct Path distance, int size, struct Point p1, struct Point p2)
{
    int i, j, k, index;
    int numberofpointone = 0, numberofpointstwo = 0;
    struct Point Arr[size];
    struct Point Top[size];
    struct Point Bottom[size];
    struct Point firstpoint;
    bool visited[size];
    memset(visited, false, size * sizeof(bool));

    double mindistance, lengthone = 0, lengthtwo = 0, checkval, a, b, c;
    //first we make line from the one end to the other, this is how we will check if were going on the upper half or the lower half of the convex hull
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = (p1.x * p2.y) - (p1.y * p2.x);

    for (i = 0; i < size; i++)
    {
        //puts the Convex hull into Arr
        Arr[i] = distance.pathPoints[i];
        if (Arr[i].x == p1.x && Arr[i].y == p1.y)
        {
            //make sure that the index that is our starting point is already marked as visited
            visited[i] = true;
        }
    }
    //setting starting point in both top and bottom
    Top[numberofpointone].x = p1.x;
    Top[numberofpointone++].y = p1.y;
    Bottom[numberofpointstwo].x = p1.x;
    Bottom[numberofpointstwo++].y = p1.x;
    for (k = 0; k < 2; k++)
    {
        //making our starting point the firstpoint that we start with aswell
        memset(visited, false, size * sizeof(bool));
        firstpoint.x = p1.x;
        firstpoint.y = p1.y;

        for (i = 0; i < size; i++)
        {
            //setting distance to max
            mindistance = DBL_MAX;
            for (j = 0; j < size; j++)
            {
                //check if the value is above or below the line and calculate distance to the nearest point
                checkval = (a * Arr[j].x) + (b * Arr[j].y) - c;
                //edge case
                if (k == 1)
                {
                    if (Arr[j].x == p2.x && Arr[j].y == p2.y)
                    {
                        checkval = 1;
                    }
                }
                double d = calculateDistance(firstpoint, Arr[j]);

                if (k == 0)
                {
                    //if the distance is smaller than min distance hasnt been visited before isnt the same point and is not below the line we set it's value
                    if (d < mindistance && visited[j] == false && d != 0 && checkval < 0)
                    {
                        mindistance = d;
                        index = j;
                    }
                }
                else
                {

                    //if the distance is smaller than min distance hasnt been visited before isnt the same point and is not above the line we set it's value
                    if (d < mindistance && visited[j] == false && d != 0 && checkval > 0)
                    {
                        mindistance = d;
                        index = j;
                    }
                }
            }

            //set the next point that we'll search from

            firstpoint.x = Arr[index].x;
            firstpoint.y = Arr[index].y;

            if (k == 0)
            {
                //top part appendinx

                lengthone += mindistance;

                Top[numberofpointone].x = Arr[index].x;
                Top[numberofpointone++].y = Arr[index].y;
            }
            else
            {

                //bottom part appending
                lengthtwo += mindistance;
                Bottom[numberofpointstwo].x = Arr[index].x;
                // printf("%lf\n", Arr[index].y);
                Bottom[numberofpointstwo++].y = Arr[index].y;
            }

            //make the index now visited
            visited[index] = true;

            //if were at end point, break
            if (firstpoint.x == p2.x && firstpoint.y == p2.y)
            {
                break;
            }
        }
    }
    //edge case
    Top[0].x = p1.x;
    //now finally check which path is shorter and add whichever is shorter to our
    if (lengthone < lengthtwo)
    {

        for (i = 0; i < numberofpointone; i++)
        {
            distance.shortestpathPoint[i].x = Top[i].x;
            distance.shortestpathPoint[i].y = Top[i].y;
        }
        distance.numOfShortPathPoints = numberofpointone;
        distance.length = lengthone;
    }
    else
    {
        for (i = 0; i < numberofpointstwo; i++)
        {
            distance.shortestpathPoint[i].x = Bottom[i].x;
            distance.shortestpathPoint[i].y = Bottom[i].y;
        }
        distance.numOfShortPathPoints = numberofpointstwo;
        distance.length = lengthtwo;
    }
    return distance;
}

int main(void)
{
    struct timespec start, end;
    FILE *fp;
    int i = 0;
    struct Path distance;
    //opening file
    fp = fopen("data_A2_Q2.txt", "r");
    if (fp == NULL)
    {
        printf("Error Failure to open file\n");
        exit(1);
    }

    struct Point Arr[MAX_LENGTH];
    struct Point p1;
    struct Point p2;
    //putting it into aray
    for (i = 0; i < MAX_LENGTH; i++)
    {
        fscanf(fp, "%lf%lf", &Arr[i].x, &Arr[i].y);
    }

    // Close the file
    fclose(fp);
    printf("please enter values of the two points\n");
    // indices of the two points s1 and s2
    scanf("%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y);
    //sample input
    // p1.x = 145.7;
    // p1.y = 517.0;
    // p2.x = 5961.6;
    // p2.y = 6274.5;
    //sorting array and getting count and time execution
    timespec_get(&start, TIME_UTC);
    distance = bruteforce(Arr, MAX_LENGTH);
    timespec_get(&end, TIME_UTC);
    distance = shortestpath(distance, distance.numOfPoints, p1, p2);
    //printing
    printf("Convex Hull:\n");
    for (i = 0; i < distance.numOfPoints; i++)
    {
        printf("%lf %lf\n", distance.pathPoints[i].x, distance.pathPoints[i].y);
    }
    printf("Number of Points around convex hull = %d\n", distance.numOfPoints);

    printf("Shortest Path Around:\n");
    for (i = 0; i < distance.numOfShortPathPoints; i++)
    {
        printf("%0.1lf %0.1lf\n", distance.shortestpathPoint[i].x, distance.shortestpathPoint[i].y);
    }
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Elapsed time: %ld ms\n", elapsed_time_ns);
    printf("Number of Points Shortest Path Around = %d\n", distance.numOfShortPathPoints);
    printf("The distance = %0.1lf\n", distance.length);
    // Print the contents of the int array
}