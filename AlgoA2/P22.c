#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>
#define MAX_LENGTH 30000
//Collin Struthers 1084915 Assignment 2 feb 12 2023
//this file contains the finding the convex hull for a file where the quicksort algorithm is used. It also displays the shortest path in the convex hull between two points inputted by the user
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
struct Path distance;
//cross product calculation
double crossProduct(struct Point p1, struct Point p2, struct Point p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}
//determine if value is on right or left side of line
int findSide(struct Point p1, struct Point p2, struct Point p)
{
    double val = crossProduct(p1, p2, p);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}
//distance calculation
double calculateDistance(struct Point a, struct Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
//finding the most right point in x  and most left point in x

void quickHull(struct Point Arr[], int size, struct Point p1, struct Point p2, int side)
{

    int index = -1;
    int i;
    double max_dist = 0;
    double crossProductAbs;
    bool found = false;
    for (i = 0; i < size; i++)
    {
        crossProductAbs = fabs(crossProduct(p1, p2, Arr[i]));
        //if there a point on the size of this new line? if not it's apart of the convex hull
        if (findSide(p1, p2, Arr[i]) == side && crossProductAbs > max_dist)
        {
            //if the tempside is the same as the side and is also the max distance apart from the points, this index will become our max distance
            index = i;
            max_dist = crossProductAbs;
        }
    }
    if (index == -1)
    {
        //if nothing is found, that means were at the end and we can add our p1 and p2 to the hull
        //checking for duplicates
        found = false;
        for (i = 0; i < distance.numOfPoints; i++)
        {
            if (distance.pathPoints[i].x == p1.x && distance.pathPoints[i].y == p1.y)
            {
                found = true;
            }
        }
        if (found == false)
        {
            distance.pathPoints[distance.numOfPoints++] = p1;
        }
        found = false;
        for (i = 0; i < distance.numOfPoints; i++)
        {
            if (distance.pathPoints[i].x == p2.x && distance.pathPoints[i].y == p2.y)
            {
                found = true;
            }
        }
        if (found == false)
        {
            distance.pathPoints[distance.numOfPoints++] = p2;
        }
        return;
    }
    //if there is a point we check to see if that point is apart of the convex hull
    quickHull(Arr, size, Arr[index], p1, -findSide(Arr[index], p1, p2));
    quickHull(Arr, size, Arr[index], p2, -findSide(Arr[index], p2, p1));
}
void hull(struct Point Arr[], int size)
{
    int min_x = 0, max_x = 0;
    //finds the max and min in the x direction
    for (int i = 1; i < size; i++)
    {
        if (Arr[i].x < Arr[min_x].x)
            min_x = i;
        if (Arr[i].x > Arr[max_x].x)
        {
            max_x = i;
        }
    }
    //send a function that look at left side of graph and one that look at right side for min_x and max_x
    quickHull(Arr, size, Arr[min_x], Arr[max_x], 1);
    quickHull(Arr, size, Arr[min_x], Arr[max_x], -1);
}
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
    //now finally check which path is shorter and add whichever is shorter to our distance struct
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
    hull(Arr, MAX_LENGTH);
    // distance = shortestpath(distance, distance.numOfPoints, p1, p2);
    timespec_get(&end, TIME_UTC);
    distance = shortestpath(distance, distance.numOfPoints, p1, p2);
    //printing results
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
}