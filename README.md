# Snakegame


# 개발 목표

1단계 목표-Map의 구현:

프로젝트의 첫 번째 단계는 Ncurses 라이브러리 함수를 사용하여 Snake 맵을 게임 화면에 출력하는 것입니다.

2단계 목표-Snake 표현 및 조작:

두 번째 단계의 목표는 Map 위에 Snake를 표시하고, 사용자로부터 화살표 키 입력을 받아 Snake가 일정 속도로 움직이도록 프로그램을 완성합니다.
Snake는 화살표 키를 통해 이동하며, 진행 방향의 반대 방향으로는 이동할 수 없습니다.
Snake의 Head가 이동할 때마다 Tail도 이동해야 하며, Tail은 진행 방향의 반대 방향으로 이동할 수 없습니다.
이동 중에 Snake의 Head가 자신의 Body에 닿거나, Gate가 아닌 Wall에 충돌하면 게임 오버됩니다.
 
3단계 목표-Item 요소의 구현:

세 번째 단계에서는 2단계 프로그램을 수정하여 Map 위에 Growth Item과 Poison Item, Special Item이 출현하도록 합니다.
Growth Item을 획득하면 10점을 얻습니다.
Poison Item을 획득하면 5점을 잃습니다.
추가로 구현한 Special Item을 획득하면 점수를 30 얻고 몸길이의 변화는 없습니다.
Growth Item과 Poison Item, Special Item은 Snake의 Body와 Wall이 없는 임의의 위치에 출현합니다.
출현 후 일정 시간이 지나면 사라지고, 다른 위치에 출현하도록 합니다.
 
4단계 목표-Gate요소의 구현:

네 번째 단계에서는 3단계 프로그램을 수정하여 Map에 Wall의 임의의 위치에 Gate가 출현할 수 있도록 합니다.
Gate는 한 쌍으로 존재하며, 게임 진행 중에 하나의 쌍만 나타납니다. 겹치지 않습니다.
Snake가 Gate에 진입하면 다른 Gate로 진출합니다.
진입 중인 경우, Gate는 사라지지 않고 다른 위치에 나타나지 않습니다.
Gate가 나타나는 벽이 가장자리에 위치할 경우, 항상 Map의 안쪽 방향으로 진출합니다.
Gate가 나타나는 벽이 Map의 안쪽에 위치할 경우, 진입 방향과 일치하는 방향이 우선이며, 진출 방향은 상황에 따라 결정됩니다.
Wall은 Gate로 변할 수 있습니다. Snake가 통과할 수 없으며, Snake Head와 충돌하면 게임 오버됩니다.
Immune Wall은 Wall이 겹치는 곳에 위치한 Wall로, Gate로 변할 수 없습니다.

5단계 목표-점수 요소의 구현:

다섯 번째 단계에서는 프로그램 우측에 게임 점수를 표시하는 Score Board를 구성합니다.
Score Board 아래에는 Mission이 포함됩니다.
Score Board는 현재 Snake의 길이, 획득한 Growth Item,Poison Item, Special Item의 수, 그리고 Gate 사용 횟수를 표시합니다.
Mission은 목표 달성 여부를 표시하며, B(Body), G(Growth Item), P(Poison Item), g(Gate) 각 항목에 대한 목표 수치를 함께 표시합니다. 


# 세부 개발 내용

1단계:

Snake Map을 게임 화면에 출력하기 위해 Ncurses 라이브러리 함수들을 사용합니다.
네가지 맵 중 키보드입력으로 선택할 수 있습니다.
Wall은 -|, 모서리는 X로 나타납니다.

2단계:

게임 화면에 Snake를 표시하고, 사용자가 화살표를 입력하면 Snake가 일정 거리를 이동하도록 프로그램을 완성합니다.
Snake의 머리는 H, 몸통은 B로 출력됩니다.
Snake는 입력된 화살표 방향으로 이동하며, 반대 방향으로 이동할 수 없도록 제한됩니다.
Snake의 머리는 이동 방향을 따라 움직이고, 꼬리는 이동할 수 없는 방향으로 이동하면 게임 오버됩니다.
게임 오버 조건은 Snake의 몸통과 충돌하거나, Gate가 아닌 Wall과 충돌하는 경우입니다.

3단계:

2단계 프로그램을 수정하여 Growth Item과 Poison Item, Special Item이 나타날 수 있도록 합니다.
Growth Item은 G, Poison Item은 P, Special Item은 S로 출력합니다.
Growth Item을 획득하면 점수를 10점 얻습니다.
Poison Item을 획득하면 점수를 5점 잃습니다.
Special Item을 획득하면 30점을 얻고 몸의 길이의 변화는 없습니다.
Growth Item과 Poison Item, Special Item은 Snake의 몸통과 Wall이 없는 임의의 Map 안에 나타납니다.
일정 시간(20주기)이 지나면 사라지고, 다른 위치에 나타날 수 있도록 합니다.

4단계:

3단계 프로그램을 수정하여 Map에 Gate 쌍이 나타날 수 있도록 합니다.
각 Gate에 Snake가 통과할 수 있도록 수정합니다.
Gate는 게임 시작과 동시에 생성됩니다.
Gate의 위치가 변경되며, Snake가 Gate를 통과하면 위치가 변경됩니다.
Gate는 한쌍씩 생성되며, 서로 겹치지 않도록 합니다.
Gate로 변할 수 있는 Wall은 게임 오버되며, Snake의 머리와 충돌할 경우 게임 오버됩니다.
Immune Wall은 Gate로 변할 수 없는 위치에 있습니다.

5단계:

프로그램에 Score Board와 Mission을 추가합니다.
Score Board는 현재 길이, 획득한 Growth Item, Poison Item, Special Item의 수, Gate 사용 횟수를 표시합니다.
Mission은 Score Board 아래에 표시되며, 각 항목에 목표 달성 여부를 표시합니다.
 

각 단계에서는 주어진 목표에 대해 필요한 로직과 알고리즘을 구현하여 결과를 달성하였습니다. 
이를 통해 사용자는 Ncurses 라이브러리를 활용한 게임 화면 출력, 사용자 입력 처리, 게임 규칙과 조건 구현, 아이템과 게이트 동작, 점수 및 미션 표시 등의 기능을 체험할 수 있습니다.
