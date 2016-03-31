from animated_list import AnimatedList
import random

def quickSort(animList, low, high):
    # low is the first element position. high is one more than the last element position
    if high - low <= 1:
        return

    # pick the first element as the pivot (and optionally, random shuffle the list)
    animList.highlight(low, color = (220,20,60))

    pivot = animList.get(low)

    yellowPointer = low + 1  # yellowPointer always points to the element next to the last element in the low part

    for greenPointer in range(low + 1, high):
        animList.highlight(greenPointer, color = (173,255,47))
        swapped = False
        if animList.get(greenPointer) <= pivot:
            swap(animList, greenPointer, yellowPointer)

            yellowPointer += 1
            swapped = True

        if swapped == False:
            animList.removeHighlight(greenPointer)

    # swap the pivot with the yellowPointer - 1 position i.e. the last element in the lower part
    animList.removeHighlight(low)

    swap(animList, yellowPointer - 1, low)

    # sort the lower half
    quickSort(animList, low, yellowPointer - 1)
    # sort the higher half
    quickSort(animList, yellowPointer, high)


def swap(animList, posA, posB):
    animList.highlight(posA)
    if posA != posB:
        animList.highlight(posB)

    temp = animList.get(posA)
    animList.set(posA, animList.get(posB))
    animList.set(posB, temp)

    animList.removeHighlight(posA)
    if posA != posB:
        animList.removeHighlight(posB)



numbers = AnimatedList()

for i in range(0,20):
    numbers.append(random.randint(1,1000))

quickSort(numbers, 0, 20)

animation = numbers.getAnimation(1000, 600, 5, 10)
animation.start(0.250)