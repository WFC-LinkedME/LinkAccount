Pod::Spec.new do |s|
s.name                  = "LinkedME_LinkAccount"
s.version              = '1.0.5'
s.summary               = "LinkedME LinkAccount"
s.description           = <<-DESC
LinkedME Deeplink for iOS.
DESC

s.homepage              = "https://github.com/WFC-LinkedME/LinkAccount.git"
s.license               = 'MIT'
s.license = { :type => 'MIT', :text => <<-LICENSE
Copyright 2019
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
LICENSE
}

s.author                = { "Bindx" => "487479@gmail.com"}
s.source                = { :git => "https://github.com/WFC-LinkedME/LinkAccount.git", :tag => s.version }

s.vendored_frameworks = '**/**/LinkAccount_Lib.framework'
s.resources = '**/**/LinkAccount.bundle'

s.libraries = 'c++', 'z.1.2.8'

s.platform              = :ios
s.ios.deployment_target = '9.0'
s.requires_arc          = true


end
