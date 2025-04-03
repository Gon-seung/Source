# 로깅
1. UE_LOG
    - UE_LOG(카테고리, 로깅 수준, 형식 문자열, 인자..)

2. 액터 움직임 제어
    - tick 함수를 이용해 매번 회전, bCanEverTice = true해야함
    - movement 객체를 만든 이후 컴포넌트를 이용해 회전, bCanEverTice = false해야함