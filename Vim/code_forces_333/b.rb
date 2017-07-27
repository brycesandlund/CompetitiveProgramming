
def main(numbers)
    odds = numbers.map { |n| n.odd? ? n : n + 1 }
    odds_length = find_greatest(odds)
    evens = numbers.map { |n| n.even? ? n : n + 1 }
    evens_length = find_greatest(evens)
    puts [odds_length, evens_length].max
end

def find_greatest(numbers)
    last_number = -100000
    in_a_row = 0
    max_in_a_row = 0
    numbers.each do |n|
        if n == last_number
            in_a_row += 1
        else
            last_number = n
            in_a_row = 1
        end
        max_in_a_row = [max_in_a_row, in_a_row].max
    end
    max_in_a_row
end

ARGF.each_with_index do |line, index|
    if index == 1
        main(line.chomp.split(' ').map(&:to_i))
    end
end
