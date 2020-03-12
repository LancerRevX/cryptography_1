function euclidean_algorithm_division_count(a, b)::UInt
    division_count = 0
    r = [a, b]
    while r[end] != 0
        push!(r, r[end-1] % r[end])
        division_count += 1
    end
    return division_count
end

using Statistics

function main()
    N = big(10)^100
    M = 1
    division_count_array = []
    while M > 0
        a, b = rand(1:N, 2)
        push!(division_count_array, euclidean_algorithm_division_count(a, b))
        M -= 1
    end
    println(mean(division_count_array))
end

main()