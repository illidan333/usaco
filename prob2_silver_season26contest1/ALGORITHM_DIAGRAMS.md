# Algorithm Flow Diagrams

## 1. Main Algorithm Flow

```mermaid
graph TD
    START["Start: Read N rods, M constraints"] --> BUILD["Build constraint graph<br/>(adjacency list)"]
    BUILD --> INIT["Initialize: done[], set_v[], ans=0"]
    INIT --> LOOP{"Any unvisited<br/>node i?"}
    
    LOOP -->|No| OUTPUT["Output answer<br/>(or -1 if impossible)"]
    LOOP -->|Yes| DFS["Start DFS from node i<br/>with expression: 1*x + 0"]
    
    DFS --> DFSPROCESS["DFS processes component:<br/>Express each rod as coef*x + const"]
    DFSPROCESS --> CYCLE{"Cycle<br/>detected?"}
    
    CYCLE -->|Contradiction| SETFLAG["Set impossible=true"]
    CYCLE -->|Consistent| COMPUTE{" Fixed value<br/>found?"}
    CYCLE -->|No cycle| COMPUTE
    
    COMPUTE -->|Yes: has_set=true| COUNT_FIXED["For set_x: count rods<br/>where l ≤ coef*set_x+c ≤ r"]
    COMPUTE -->|No: has_set=false| SWEEP["Sweep-line algorithm:<br/>Find max interval coverage"]
    
    COUNT_FIXED --> ADD["Add count to ans"]
    SWEEP --> ADD
    ADD --> MARK["Mark component done"]
    MARK --> LOOP
    
    SETFLAG --> OUTPUT
    
    OUTPUT --> END["End"]
    
    style START fill:#e1f5ff
    style END fill:#e1f5ff
    style SETFLAG fill:#ffcdd2
    style OUTPUT fill:#c8e6c9
```

## 2. DFS Constraint Propagation

```mermaid
graph TD
    DFSTART["DFS(node i, expr: coef*x + const)"] --> CHECK{"Node i<br/>visited?"}
    
    CHECK -->|Yes| COMPARE{"expr matches<br/>set_v[i]?"}
    COMPARE -->|No match| SOLVE["Solve for x:<br/>set_v[i].coef*x + set_v[i].const = coef*x + const"]
    SOLVE --> VALID{"Integer<br/>solution?"}
    VALID -->|No| IMPOSSIBLE["Mark impossible"]
    VALID -->|Yes| FIXCHECK{"Value already<br/>fixed?"}
    FIXCHECK -->|No| FIX["Fix x to solution"]
    FIXCHECK -->|Yes| VERIFY{"Matches<br/>fixed value?"}
    VERIFY -->|No| IMPOSSIBLE
    VERIFY -->|Yes| OK["OK"]
    COMPARE -->|Match| OK
    
    CHECK -->|No| PROCESS["Mark node done<br/>Store expression<br/>Add to mod list"]
    PROCESS --> RANGE["Calculate valid range<br/>l ≤ coef*x + const ≤ r"]
    RANGE --> ADDINTERVAL["Add interval endpoints<br/>to mod list"]
    ADDINTERVAL --> RECURSE["For each neighbor j<br/>DFS(j, -coef*x + z-const)"]
    
    IMPOSSIBLE --> DFSEND["Return"]
    OK --> DFSEND
    RECURSE --> DFSEND
    
    style DFSTART fill:#fff9c4
    style IMPOSSIBLE fill:#ffcdd2
    style OK fill:#c8e6c9
```

## 3. Sweep Line Algorithm (Free Variable Case)

```mermaid
graph TD
    SWEEP["Sweep Line: Find max interval coverage"] --> COLLECT["For each rod j:<br/>Determine range of x<br/>where rod is valid"]
    
    COLLECT --> CREATE["Create events:<br/>[range_start, +1] and [range_end+1, -1]"]
    CREATE --> SORT["Sort all events by x-coordinate"]
    SORT --> PROCESS["Process events in order:<br/>Track active count"]
    
    PROCESS --> INIT["current_count = 0<br/>max_count = 0"]
    INIT --> LOOP["For each event:"]
    
    LOOP --> APPLY["current_count += event.delta"]
    APPLY --> UPDATE["max_count = max(max_count, current_count)"]
    UPDATE --> CHECK{"More<br/>events?"}
    CHECK -->|Yes| LOOP
    CHECK -->|No| RESULT["Return max_count<br/>this many rods can generate power"]
    
    style SWEEP fill:#fff9c4
    style RESULT fill:#c8e6c9
```

## 4. Example: Test Case 2 Execution

```mermaid
graph TD
    INPUT["N=3, M=2<br/>l=[10,-10,10], r=[10,-10,10]<br/>Constraints: a₁+a₂=0, a₂+a₃=0"]
    
    INPUT --> GRAPH["Build Graph:<br/>1 -- 0 -- 2 -- 0 -- 3"]
    
    GRAPH --> DFS1["DFS(1, 1x+0)"]
    DFS1 --> DFS2["a₁ = 1x + 0<br/>DFS(2, -1x+0)"]
    DFS2 --> DFS3["a₂ = -1x + 0<br/>DFS(3, 1x+0)"]
    DFS3 --> DFSEND["a₃ = 1x + 0<br/>No cycles"]
    
    DFSEND --> INTERVALS["Calculate intervals for free variable x:<br/>Rod 1: 10 ≤ 1x+0 ≤ 10 → [10,11)<br/>Rod 2: -10 ≤ -1x+0 ≤ -10 → [10,11)<br/>Rod 3: 10 ≤ 1x+0 ≤ 10 → [10,11)"]
    
    INTERVALS --> SWEEP["Sweep line:<br/>All rods: [10,+1], [11,-1]"]
    SWEEP --> MAX["At x=10: count = 3"]
    MAX --> ANS["Answer = 3"]
    
    style INPUT fill:#e3f2fd
    style ANS fill:#c8e6c9
```

## 5. Data Structure Relationships

```mermaid
graph LR
    GRAPH["Graph:<br/>adj[i] = {j, z}"] 
    EXPR["Linear Expression:<br/>set_v[i] = {coef, const}"]
    INTERVALS["Interval List:<br/>mod = {x, delta}"]
    
    DFS["DFS Process"]
    
    GRAPH --> DFS
    DFS --> EXPR
    EXPR --> INTERVALS
    INTERVALS --> SWEEP["Sweep Line"]
    SWEEP --> ANSWER["Maximum Rods"]
    
    style ANSWER fill:#c8e6c9
```

## 6. State Transitions During DFS

```mermaid
stateDiagram-v2
    [*] --> Unvisited: Start
    
    Unvisited --> Visiting: Mark visited
    Visiting --> Visiting: Traverse edges
    
    Visiting --> FixedValue: Cycle with<br/>fixed solution
    Visiting --> FreeVariable: No cycle or<br/>no constraint
    
    Visiting --> Impossible: Contradiction
    
    FixedValue --> Done: Count valid<br/>in range
    FreeVariable --> Done: Sweep-line<br/>optimization
    
    Impossible --> Done: Return -1
    
    Done --> [*]
    
    note right of Visiting
        Process node:
        - Add to done[]
        - Store expression
        - Recurse to neighbors
    end note
    
    note right of FixedValue
        Cycle creates equation:
        set_v[i] = new_expr
        Solve for x value
    end note
    
    note right of FreeVariable
        No cycle or 
        free variable remains
        Use sweep-line to maximize
    end note
```

## 7. Problem Complexity Visualization

```mermaid
graph TD
    COMPONENTS["Problem splits into<br/>K connected components"]
    
    COMPONENTS --> C1["Component 1:<br/>n₁ nodes<br/>m₁ edges"]
    COMPONENTS --> C2["Component 2:<br/>n₂ nodes<br/>m₂ edges"]
    COMPONENTS --> CK["Component K:<br/>nₖ nodes<br/>mₖ edges"]
    
    C1 --> DFS1["DFS: O(n₁+m₁)<br/>Solve independent"]
    C2 --> DFS2["DFS: O(n₂+m₂)<br/>Solve independent"]
    CK --> DFSK["DFS: O(nₖ+mₖ)<br/>Solve independent"]
    
    DFS1 --> TOTAL["Total DFS: O(n+m)"]
    DFS2 --> TOTAL
    DFSK --> TOTAL
    
    TOTAL --> SORT["Sort intervals:<br/>O((n+m)log(n+m))"]
    SORT --> SWEEP["Sweep-line:<br/>O(n+m)"]
    SWEEP --> FINAL["Final: O(n+m)log(n+m)"]
    
    style FINAL fill:#c8e6c9
```

## Algorithm Correctness

### Invariant 1: Linear Expressions
- Each rod's energy has exactly one linear expression in terms of component representative
- Expression is unique after first assignment

### Invariant 2: Cycle Consistency
- If cycle exists, it must be consistent or determine fixed value
- Inconsistent cycle → return -1

### Invariant 3: Interval Maximization
- For free variable: max valid rods = max overlapping intervals at any point
- Sweep-line algorithm finds this maximum correctly

### Proof Sketch
1. **Correctness of DFS:** Each rod connected to representative via unique path
2. **Correctness of cycle handling:** Linear algebra ensures valid solutions
3. **Correctness of sweep-line:** Standard interval scheduling algorithm
4. **Independence of components:** No constraints between components → can solve separately
5. **Completeness:** All cases covered (fixed value, free variable, impossible)
