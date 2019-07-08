Pod::Spec.new do |s|
s.name                  = "LinkedME_LinkAccount"
s.version              = '1.0.3'
s.summary               = "LinkedME LinkAccount"
s.description           = <<-DESC
LinkedME Deeplink for iOS.
DESC

s.homepage              = "https://github.com/WFC-LinkedME/LinkAccount.git"
s.license               = 'MIT'
s.author                = { "Bindx" => "487479@gmail.com"}
s.source                = { :git => "https://github.com/WFC-LinkedME/LinkAccount.git", :tag => s.version }

s.vendored_frameworks = '**/**/LinkAccount_Lib.framework'
s.resources = '**/**/LinkAccount.bundle'

s.libraries = 'c++', 'z.1.2.8'

s.platform              = :ios
s.ios.deployment_target = '9.0'
s.requires_arc          = true


end
